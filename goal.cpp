#include "goal.h"

Goal::Goal() {}

Goal::~Goal() {}

MoveResult Goal::checkMoveOnto(Entity*, const Position& fromPos, const Position& tilePos) const noexcept {
	return MoveResult::ALLOW;
}

bool Goal::isGoal() const noexcept {
	return true;
}

std::string Goal::getGlyph() const noexcept {
	return "<";
}
