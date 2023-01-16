#include "floor.h"

Floor::Floor() {}

Floor::~Floor() {}

MoveResult Floor::checkMoveOnto(Entity* entity, const Position&, const Position&) const noexcept {
	return MoveResult::ALLOW;
}

bool Floor::isGoal() const noexcept {
	return false;
}

std::string Floor::getGlyph() const noexcept {
	return ".";
}
