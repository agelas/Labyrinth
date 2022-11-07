#pragma once

#include "wall.h"
#include "floor.h"
#include "goal.h"
#include <stdexcept>

class Tile;

// Singleton factory to create Tile objects
class TileFactory {
private:
	// copy constructor and assignment operator are disallowed
	TileFactory(const TileFactory&);
	TileFactory& operator=(const TileFactory&);

	// constructor and destructor are private
	TileFactory();
	~TileFactory();

public:
	static TileFactory* getInstance();
	Tile* createFromChar(char c);
};