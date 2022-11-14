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

std::unique_ptr<Maze> Game::getMaze() {
	return std::move(maze);
}

UI* Game::getUI() {
	return this->ui;
}

GameRules* Game::getGameRules() {
	return this->gameRules;
}

void Game::gameLoop() {
	/*
		TODO:
		Let the Entity objects take turns in a round-robin
		fashion until the GameRules object determines that
		the hero has won or lost.
	*/
	return;
}

void Game::takeTurn(Entity* actor) {
	/*
		TODO: 
		Let specified actor Entity take a turn.
	*/
	return;
}

Game* Game::loadGame(std::istream& in) {
	/*
		Read initial Game data in from the specified istream,
		and return the resulting Game object

		TODO:
		Deal with Entity construction
	*/
	Game* game = new Game();
	game->maze = Maze::read(in);

	return game;
}



