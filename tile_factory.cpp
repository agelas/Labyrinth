#include "tile_factory.h"

TileFactory::TileFactory() {}

TileFactory::~TileFactory() {}

TileFactory* TileFactory::getInstance() {
	static TileFactory theInstance;
	return &theInstance;
}

Tile* TileFactory::createFromChar(char c) {
	switch (c) {
	case '.':
		return new Floor();
	case '#':
		return new Wall();
	case '<':
		return new Goal();
	default:
		throw std::runtime_error("Not a valid tile character");
	}
}