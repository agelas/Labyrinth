#pragma once

#include <string>

// Forward declare Position and Entity later

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
	
	// virtual MoveResult checkMoveOnto

	virtual bool isGoal() const = 0;

	virtual std::string getGlyph() const = 0;

	virtual ~Tile();
};
