#include "SimpleChaser.h"

SimpleChaser::SimpleChaser() {}

SimpleChaser::~SimpleChaser() {}

Direction SimpleChaser::getMoveDirection(Game* game, Entity* entity) {

	// Get hero position
	std::vector<Entity*> heroVector = game->getEntitiesWithProperty('h');

	// Get closest hero's position
	Position closestHeroPosition = heroVector[0]->getPosition();

	for (int i = 1; i < (int)heroVector.size(); i++) {
		Position currentHeroPosition = heroVector[i]->getPosition();
		if (entity->getPosition().distanceFrom(currentHeroPosition) < entity->getPosition().distanceFrom(closestHeroPosition)) {
			closestHeroPosition = currentHeroPosition;
		}
	}

	// Get minotaur's position
	Position minoPosition = entity->getPosition();

	// Find all legal moves
	// TODO: Find a less ugly way of doing this part
	Position right = minoPosition.displace(Direction::RIGHT);
	Position left = minoPosition.displace(Direction::LEFT);
	Position up = minoPosition.displace(Direction::UP);
	Position down = minoPosition.displace(Direction::DOWN);
	std::vector<Position> allMoves {right, left, up, down};

	Position bestPosition = allMoves[0]; 
	int j = -1; // Index for position in allMoves that minimizes distance
	int bestDistance = pow(minoPosition.getX() - closestHeroPosition.getX(), 2) 
		+ pow(minoPosition.getY() - closestHeroPosition.getY(), 2); // Initialize to current distance between minotaur and hero


	for (int i = 0; i < (int)allMoves.size(); i++) {
		int distanceToHero = pow(allMoves[i].getX() - closestHeroPosition.getX(), 2) + pow(allMoves[i].getY() - closestHeroPosition.getY(), 2);
		if (game->getGameRules()->allowMove(game, entity, minoPosition, allMoves[i]) && distanceToHero < bestDistance) {
			j = i;
			bestDistance = distanceToHero;
		}
	}

	// This is such a bad way of doing this lol
	switch (j) {
	case 0:
		return Direction::RIGHT;
	case 1:
		return Direction::LEFT;
	case 2:
		return Direction::UP;
	case 3:
		return Direction::DOWN;
	default:
		return Direction::NONE;
	}
}

bool SimpleChaser::isUser() const {
	return false;
}
