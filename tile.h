#pragma once

#include <string>

class Position;
class Entity;

enum class MoveResult {
	ALLOW,
	BLOCk,
};

class Tile {
private:
	Tile(const Tile&);
	Tile& operator=(const Tile&);

public:
	Tile();
	
	virtual MoveResult checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const = 0;

	virtual bool isGoal() const = 0;

	virtual std::string getGlyph() const = 0;

	virtual ~Tile();
};
