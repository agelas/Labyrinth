#include "maze.h"

Maze::Maze(int width, int height) {
	this->width = width;
	this->height = height;

	for (int i = 0; i < width * height; i++) {
		grid.push_back(NULL);
	}
}

Maze::~Maze() {
	for (int i = 0; i < width * height; i++) {
		delete grid[i];
	}
}

int Maze::getWidth() const {
	return width;
}

int Maze::getHeight() const {
	return height;
}

bool Maze::inBounds(const Position& pos) const {
	return (pos.getX() < width && pos.getY() < height && 
		pos.getX() > 0 && pos.getY() > 0);
}

void Maze::setTile(const Position& pos, Tile* tile) {
	grid[pos.getY() * width + pos.getX()] = tile;
}

const Tile* Maze::getTile(const Position& pos) const {
	const Tile* tile = grid[pos.getY() * width + pos.getX()];
	return tile;
}

std::unique_ptr<Maze> Maze::read(std::istream& in) {
	char t;
	// First two ints read are the width and height of the maze
	std::string line;
	std::getline(in, line);
	int ws = line.rfind(" "); // Dimensions should be seperated by a white space

	// If no white space then a dimension is missing and maze isn't valid
	if (ws == -1) { 
		throw std::runtime_error("Invalid maze read instructions");
	} 

	int w = stoi(line.substr(0, ws));
	int h = stoi(line.substr(ws + 1));

	if (w < 0 || h < 0) { 
		throw std::runtime_error("Invalid maze dimensions"); 
	} // Maze dimensions can't be negative

	std::unique_ptr<Maze> maze = std::make_unique<Maze>(w, h);

	TileFactory* tf;

	tf = TileFactory::getInstance();

	for (int i = 0; i < h; i++) {
		std::getline(in, line);
		if ((int)line.length() != w) {
			throw std::runtime_error("Invalid line length");
		}

		for (int j = 0; j < w; j++) {
			t = line[j];
			Tile* tile = tf->createFromChar(t);
			if (!(tile)) {
				throw std::runtime_error("Invalid character");
			}
			const Position& pos = Position(j, i);
			maze->setTile(pos, tile);
		}
	}
	return maze;
}

void Maze::print() const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Position p = Position(j, i);
			const Tile* t = this->getTile(p);
			std::cout << t->getGlyph();
		}
		std::cout << std::endl;
	}
}