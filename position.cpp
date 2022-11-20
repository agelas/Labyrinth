#include "position.h"

Position& Position::operator=(const Position& rhs) {
    if (this != &rhs) {
       x = rhs.x;
       y = rhs.y;
    }
    return *this;
}

bool Position::operator==(const Position& rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool Position::operator!=(const Position& rhs) const {
    return !(*this == rhs);
}

bool Position::operator<(const Position& rhs) const {
    if (y < rhs.y) {
        return true;
    }
    else if (y > rhs.y) {
        return false;
    }
    else {
        return x < rhs.x;
    }
}

int Position::getX() const {
    return x;
}

int Position::getY() const {
    return y;
}

// Return the Position that is displaced by moving 1 step in the specified direction.
// Useful for carrying out moves or evaluating hypothetical moves.
Position Position::displace(Direction dir) const {
    switch (dir) {
    case Direction::UP:
        return Position(x, y - 1);
    case Direction::DOWN:
        return Position(x, y + 1);
    case Direction::LEFT:
        return Position(x - 1, y);
    case Direction::RIGHT:
        return Position(x + 1, y);
    case Direction::NONE:
        return *this;
    }
    throw std::runtime_error("Unknow direction");
}

// Get distance from this Position instance to another one.
int Position::distanceFrom(const Position& other) const {
    int xDiff = abs(x - other.x);
    int yDiff = abs(y - other.y);
    return xDiff + yDiff;
}

// Determine whether this Position is in bounds on a grid with specified width and height
bool Position::inBounds(int width, int height) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

