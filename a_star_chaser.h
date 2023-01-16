#pragma once
#include "entity_controller.h"
#include "position.h"
#include "game.h"
#include <map>
#include <vector>
#include <string>

class AStarChaser : public EntityController {
private:
	AStarChaser(const AStarChaser&);
	AStarChaser& operator=(const AStarChaser&);

	std::vector<char> allDirections = { 'r', 'l', 'u', 'd' };

	void pathExtension(Game *game, std::vector<Position> pastPositions, std::string path, Position curPos, const Position& heroPos, std::map<int, std::string>& pathMap, Entity* entity);
	bool checkMove(Game* game, std::vector<Position> pastPositions, const Position& source, const Position& hypotheticalPos, Entity* entity);

public:
	AStarChaser();
	virtual ~AStarChaser();
	virtual Direction getMoveDirection(Game* game, Entity* entity) override;
	virtual bool isUser() const override;
};