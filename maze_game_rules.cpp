#include "maze_game_rules.h"

MazeGameRules::MazeGameRules() {}
MazeGameRules::~MazeGameRules() {}

bool MazeGameRules::allowMove(Game* game, Entity* actor, const Position& source, const Position& dest) const{

	// Do not allow a move that is not in the maze
	if (!(dest.inBounds(game->getMaze()->getWidth(), game->getMaze()->getHeight()))) { return false; }

	// Do not allow a move that is more than one tile
	if (source.distanceFrom(dest) > 1) { return false; }

	// Do not allow a move onto a tile that blocks 
	if (game->getMaze()->getTile(dest)->checkMoveOnto(actor, source, dest) == MoveResult::BLOCk) { return false; }

	Entity* entityDestination = game->getEntityAt(dest);

	if (entityDestination) {
		// Can move onto entity as long as it's not moveable
		if (!(entityDestination->hasProperty('v'))) { return false; }
		
		// Can't push a moveable entity onto another moveable entity
		const Position checkPosition = inanimateDestination(source, dest);
		if (game->getEntityAt(checkPosition)) { return false; }

		// Check if entity can push moveable entity onto a tile
		if (game->getMaze()->getTile(checkPosition)->checkMoveOnto(entityDestination, dest, checkPosition) != MoveResult::ALLOW) {
			return false;
		}

		// Moveable entity can't be pushed onto goal
		if (game->getMaze()->getTile(checkPosition)->isGoal()) {
			return false;
		}

		// Cannot push movable entity out of the maze
		if (!(checkPosition.inBounds(game->getMaze()->getWidth(), game->getMaze()->getHeight()))) {
			return false;
		}

		// Cannot push moveable entity more than one tile at a time
		if (checkPosition.distanceFrom(dest) > 1) {
			return false;
		}
	}
	return true;
}

void MazeGameRules::enactMove(Game* game, Entity* actor, const Position& dest) const {
	Position source = actor->getPosition();
	Entity* entityDest = game->getEntityAt(dest);

	// Check if there already is an entity at the position
	if (entityDest) {
		// Allow minotaur to move onto a position with hero
		if (entityDest->hasProperty('m') && actor->hasProperty('h') && !(entityDest->hasProperty('v'))) {
			actor->setPosition(dest);
		}
		// Allow hero to move onto a position with minotaur
		else if (entityDest->hasProperty('m') && actor->hasProperty('h') && !(entityDest->hasProperty('v'))) {
			actor->setPosition(dest);
		}
		// Allow hero to move onto an inanimate object
		else {
			entityDest->setPosition(inanimateDestination(source, dest));
			actor->setPosition(dest);
		}
	}
	else {
		// If there's nothing occupying the position, then set position there
		actor->setPosition(dest);
	}
}

GameResult MazeGameRules::checkGameResult(Game* game) const {
	std::vector<Entity*> entityVec = game->getEntities();
	Position p;
	for (int i = 0; i < (int)entityVec.size(); i++) {
		if (entityVec[i]->hasProperty('h')) { // Find all hero entities
			p = entityVec[i]->getPosition();
			// Check if hero is on goal
			if (game->getMaze()->getTile(p)->isGoal()) {
				return GameResult::HERO_WINS;
			}
		}
	}
	for (int j = 0; j < (int)entityVec.size(); j++) { // Check if any minotaurs on heroes
		if (entityVec[j]->hasProperty('m') && entityVec[j]->getPosition() == p) {
			return GameResult::HERO_LOSES;
		}
	}
	// If none of the previous conditions are met, then game is still ongoing
	return GameResult::UNKNOWN;
}

const Position MazeGameRules::inanimateDestination(const Position& source, const Position& dest) const{
/*
	Takes in two position objects. Function will return the position of the inanimate object
	starting at position source, and ending at the position it is moved onto.
*/
	int x1, x2, y1, y2, dx, dy;
	x1 = source.getX();
	x2 = dest.getX();
	y1 = source.getY();
	y2 = dest.getY();

	dx = x2 - x1;
	dy = y2 - y1;
	Position inanimate = Position(x2 + dx, y2 + dy);
	return inanimate;
}