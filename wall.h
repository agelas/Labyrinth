#pragma once

#include "tile.h"
#include "entity.h"
#include "position.h"
#include <string>

class Wall : public Tile {
private:
	Wall(const Wall&);
	Wall& operator=(const Wall&);

public:
	Wall();

	virtual MoveResult checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const noexcept;
	virtual bool isGoal() const noexcept;
	virtual std::string getGlyph() const noexcept;

	virtual ~Wall();
};