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
		[[unlikely]];
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

void AStarChaser::pathExtension(Game* game, std::vector<Position> pastPositions, std::string path, Position curPos, const Position& heroPos, std::map<int, std::string>& pathMap, Entity* entity) {
	/*
	Recursively extends paths until all successful paths (paths that reach hero) are stored in the map.
	If the current path's cost is larger than the smallest cost in the map, the path is ignored.
	Paths are composed of chars representing one of the four directions that the minotaur is allowed to move.
	*/
	int cost = path.length() + curPos.distanceFrom(heroPos);
	int maxSize = pathMap.begin()->first;
	vector<Position> newPastPositions = pastPositions;
	vector<Position> allMoves;
	
	if (cost >= maxSize) {
		return;
	}

	if (curPos == heroPos) {
		pathMap[cost] = path;
		return;
	}

	newPastPositions.push_back(curPos);

	// Get valid moves, order needs to follow class's allDirections vector
	Position right = curPos.displace(Direction::RIGHT);
	allMoves.push_back(right);
	Position left = curPos.displace(Direction::LEFT);
	allMoves.push_back(left);
	Position up = curPos.displace(Direction::UP);
	allMoves.push_back(up);
	Position down = curPos.displace(Direction::DOWN);
	allMoves.push_back(down);

	for (int i = 0; i < allMoves.size(); i++) {
		if (checkMove(game, pastPositions, curPos, allMoves[i], entity)) {
			string newPath = path;
			newPath.push_back(allDirections[i]);
			pathExtension(game, newPastPositions, newPath, allMoves[i], heroPos, pathMap, entity);
		}
	}
	return;
}