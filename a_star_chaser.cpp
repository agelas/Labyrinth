#include "a_star_chaser.h"

using std::map;
using std::vector;
using std::string;

AStarChaser::AStarChaser() {}

AStarChaser::~AStarChaser() {}

Direction AStarChaser::getMoveDirection(Game* game, Entity* entity) {
	map<int, string> initial;
	initial[INT_MAX] = "temp";
	vector<Position> pastPositions;
	string path;

	//The key is an int so we can automatically sort by ascending order.
	//The key is treated as the cost of the path.
	map<int, string>& pathMap = initial;

	Position curPos = entity->getPosition();

	vector<Entity*> hvec = game->getEntitiesWithProperty('h');

	Position heroPos = hvec[0]->getPosition(); // Initialize heroPos to first hero in hvec

	// Retrieve nearest hero's position
	for (int i = 1; i < hvec.size(); i++) {
		Position curHeroPos = hvec[i]->getPosition();
		if (entity->getPosition().distanceFrom(curHeroPos) < entity->getPosition().distanceFrom(heroPos)) {
			heroPos = curHeroPos;
		}
	}

	pathExtension(game, pastPositions, path, curPos, heroPos, pathMap, entity);

	char instruction = pathMap.begin()->second[0]; //First char from first value of the pathMap will be path with the smallest cost

	switch (instruction) { //Translate instruction into a direction
	case 'u':
		return Direction::UP;
	case 'd':
		return Direction::DOWN;
	case 'l':
		return Direction::LEFT;
	case 'r':
		return Direction::RIGHT;
	default:
		return Direction::NONE;
	}
}

bool AStarChaser::isUser() const {
	return false;
}

bool AStarChaser::checkMove(Game* game, std::vector<Position> pastPositions, const Position& source, const Position& hypotheticalPos, Entity* entity) {
	/*
	Determines if the hypotheical position that the minotaur wants to move to
	is allowed, and if it's not already one that the minotaur has visited on
	its path
	*/

	if (game->getGameRules()->allowMove(game, entity, source, hypotheticalPos)) {
		for (int i = 0; i < pastPositions.size(); i++) {
			if (pastPositions[i] == hypotheticalPos) {
				return false; // Check if hypothetical poisition has already been visited
			}
		}
	}
	else {
		return false;
	}
	return true;
}