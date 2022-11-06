#pragma once

#include "tile.h"
#include "entity.h"
#include "position.h"
#include <string>

class Floor : public Tile {
private:
	Floor(const Floor&);
	Floor& operator=(const Floor&);

public:
	Floor();

	virtual MoveResult checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const;
	virtual bool isGoal() const;
	virtual std::string getGlyph() const;
	
	virtual ~Floor();
};