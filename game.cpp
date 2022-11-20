#include "game.h"

Game::Game() {
	this->maze = NULL;
	this->ui = NULL;
	this->gameRules = NULL;
}

Game::~Game() {
	delete this->ui;
	delete this->gameRules;
	for (int i = 0; i < (int)evec.size(); i++) {
		delete evec[i];
	}
}

void Game::setMaze(std::unique_ptr<Maze> maze) {
	this->maze = std::move(maze);
}

void Game::setUI(UI* ui) {
	this->ui = ui;
}

void Game::setGameRules(GameRules* gameRules) {
	this->gameRules = gameRules;
}

void Game::addEntity(Entity* entity) {
	/*
		Add an Entity to the sequence of entities. The game object
		assumes responsibility for deleting it.
	*/
	evec.push_back(entity);
}

Entity* Game::getEntityAt(const Position& pos) {
	/*
		Retrieve the Entity at the specified location. 
		Return nullptr if there is no Entity there.
		
		TODO: The internal if-else if looks weird 
	*/
	Entity* e = NULL;
	for (int i = 0; i < (int)evec.size(); i++) {
		if (evec[i]->getPosition() == pos) {
			if (e == NULL) {
				e = evec[i];
			}
			else if (evec[i]->hasProperty('m')) {
				e = evec[i];
			}
		}
	}
	return e;
}

const Game::EntityVec& Game::getEntities() const {
	/*
		Get a const reference to the Game object's internal
		vector of pointers to Entity objects
	*/
	return evec;
}

Game::EntityVec Game::getEntitiesWithProperty(char prop) const {
	/*
		Return a vector of pointers to Entity objects that have 
		the specified property. Vector can potentially be empty.
	*/
	Game::EntityVec evec_prop;
	for (int i = 0; i < (int)evec.size(); i++) {
		if (evec[i]->hasProperty(prop)) {
			evec_prop.push_back(evec[i]);
		}
	}
	return evec_prop;
}

Maze& Game::getMaze() {
	return *maze;
}

UI* Game::getUI() {
	return this->ui;
}

GameRules* Game::getGameRules() {
	return this->gameRules;
}

void Game::gameLoop() {
	/*
		Let the Entity objects take turns in a round-robin
		fashion until the GameRules object determines that
		the hero has won or lost.
	*/

	do {
		for (int i = 0; i < (int)evec.size(); i++) {
			if ((evec[i]->getController())->isUser()) {
				ui->render(this);
			}
			takeTurn(evec[i]);
			if (gameRules->checkGameResult(this) != GameResult::UNKNOWN) {
				break;
			}
		}
	} while (gameRules->checkGameResult(this) != GameResult::UNKNOWN);

	// Check and print game result
	std::string message;
	if (gameRules->checkGameResult(this) == GameResult::HERO_WINS) {
		message = ": Hero wins";
	}
	else {
		message = ": Hero loses";
	}
	ui->displayMessage(message, true);
	ui->render(this);
}

void Game::takeTurn(Entity* actor) {
	/* 
		Let specified actor Entity take a turn.
	*/
	Direction move = actor->getController()->getMoveDirection(this, actor);
	Position p = (actor->getPosition()).displace(move);

	// Check if entity is allowed to move in that direction
	if (gameRules->allowMove(this, actor, actor->getPosition(), p)) {
		gameRules->enactMove(this, actor, p);
	}
	else {
		ui->displayMessage(": Illegal move", false);
	}
}

Game* Game::loadGame(std::istream& in) {
	/*
		Read initial Game data in from the specified istream,
		and return the resulting Game object
	*/
	Game* game = new Game();
	game->setMaze(Maze::read(in));

	std::string entity_string;
	std::string in_x; // String from maze file for x coord
	std::string in_y;
	int x, y;

	EntityControllerFactory* eCFactory;
	eCFactory = EntityControllerFactory::getInstance();

	while (in >> entity_string && in >> in_x && in >> in_y) {
		x = std::stoi(in_x);
		y = std::stoi(in_y);

		// TODO: probably a check to make sure coordinates are valid

		Entity* newEntity = new Entity();
		newEntity->setController(eCFactory->createFromChar(entity_string[1]));
		newEntity->setGlyph(entity_string.substr(0, 1));
		Position p = Position(x, y);
		newEntity->setPosition(p);
		newEntity->setProperties(entity_string.substr(2));

		game->addEntity(newEntity);
	}

	EntityVec eVectorCheck = game->getEntities();
	if (eVectorCheck.empty()) {
		throw std::runtime_error("No Entities Created");
	}

	return game;
}



