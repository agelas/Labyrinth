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
	//The key is is treated as the cost of the path.
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