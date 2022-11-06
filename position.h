#pragma once

#include <stdexcept>
#include <iostream>

enum class Direction {
	UP, DOWN, LEFT, RIGHT, NONE,
};

/*
	A Position object represent an x,y coordinate within a maze. 
	Position objects have value semantics (can be copied and assigned).
*/

class Position {
private:
	int x, y;

public:
	// Default constructor
	Position() : x(0), y(0) {}

	// Constructor from x,y coordinates
	Position(int x, int y) : x(x), y(y) {}

	// Copy constructor
	Position(const Position& other) : x(other.x), y(other.y) {}

	// Operator overloads
	Position& operator = (const Position& rhs);
	bool operator==(const Position& rhs) const;
	bool operator!=(const Position& rhs) const;
	bool operator<(const Position& rhs) const;

	friend std::ostream& operator<<(std::ostream& out, const Position& pos) {
		out << pos.getX() << "," << pos.getY();
		return out;
	}
	
	// Class Functions
	int getX() const;
	int getY() const;
	Position displace(Direction dir) const;
	int distanceFrom(const Position& other) const;
	bool inBounds(int width, int height) const;

	~Position() {}
};