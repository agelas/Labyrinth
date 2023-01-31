#pragma once
#include "entity_controller.h"
#include "position.h"
#include "game.h"
#include <map>
#include <vector>
#include <string>

class DjikstraChaser : public EntityController {
private:
	DjikstraChaser(const DjikstraChaser&);
	DjikstraChaser& operator=(const DjikstraChaser&);

	std::vector<char> allDirection = { 'r', 'l', 'u', 'd' };

	void pathExtension(Game* game, std::vector<Position> pastPositions, std::string path, Position curPos, const Position& heroPos, std::map<int, std::string>& pathMap, Entity* entity);
	bool checkMove(Game* game, std::vector<Position> pastPositions, const Position& source, const Position& hypotheticalPos, Entity* entity);

public:
	DjikstraChaser();
	virtual ~DjikstraChaser();
	virtual Direction getMoveDirection(Game* game, Entity* entity) override;
	bool isUser() const noexcept override;
};