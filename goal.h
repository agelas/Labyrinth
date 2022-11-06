#pragma once

#include "tile.h"
#include "position.h"
#include "entity.h"
#include <string>

class Goal : public Tile {
private: 
	Goal(const Goal&);
	Goal& operator=(const Goal&);

public:
	Goal();

	virtual MoveResult checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const override;
	virtual bool isGoal() const override;
	virtual std::string getGlyph() const override;

	virtual ~Goal();
};