#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include "tile.h"
#include "entity.h"
#include "position.h"
#include "tile_factory.h"

class Tile;
class Entity;
class Position;

// A maze is a grid of Tile objects
class Maze {
private:
	int width;
	int height;
	std::vector<Tile*> grid;

	Maze(const Maze&);
	Maze& operator=(const Maze&);

public:
	Maze(int width, int height);
	int getWidth() const;
	int getHeight() const;
	bool inBounds(const Position& pos) const;
	void setTile(const Position& pos, Tile* tile);
	const Tile* getTile(const Position& pos) const;
	static std::unique_ptr<Maze> read(std::istream& in);
	void print() const;

	~Maze();
};