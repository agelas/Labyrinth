#include "wall.h"

Wall::Wall() {}

Wall::~Wall() {}

MoveResult Wall::checkMoveOnto(Entity* entity, const Position& fromPos, const Position& tilePos) const noexcept {
    return MoveResult::BLOCk;
}

bool Wall::isGoal() const noexcept {
    return false;
}

std::string Wall::getGlyph() const noexcept {
    return "#";
}
