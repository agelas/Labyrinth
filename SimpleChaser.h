#pragma once

#include "game.h"
#include "entity.h"
#include "entity_controller.h"
#include "maze_game_rules.h"
#include <cmath>
#include <vector>
#include <cassert>

/*
	SimpleChaser is an implementation of EntityController that
	chases the user's character/hero by moving one tile closer
	each turn. 
*/
class SimpleChaser : public EntityController {
private:
	SimpleChaser(const SimpleChaser&);
	SimpleChaser& operator=(const SimpleChaser&);

public:
	SimpleChaser();

	virtual Direction getMoveDirection(Game* game, Entity* entity) override;
	virtual bool isUser() const override;

	virtual ~SimpleChaser();
};
