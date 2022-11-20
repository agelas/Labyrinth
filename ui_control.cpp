#include "ui_control.h"

UIControl::UIControl() {}

UIControl::~UIControl() {}

Direction UIControl::getMoveDirection(Game* game, Entity*) {
	UI* ui = game->getUI();
	Direction dir = ui->getMoveDirection();
	return dir;
}

bool UIControl::isUser() const {
	return true;
}
