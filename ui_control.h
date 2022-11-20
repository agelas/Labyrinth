#pragma once

#include "entity_controller.h"
#include "game.h"
#include "ui.h"

/*
	UIControl is an EntityController implementation which uses
	the singleton UI object to determine the reuested move
	direction for the controlled entity. 

	Long story short this is the Entity the user controls via
	the command line.
*/
class UIControl : public EntityController {
private:
	UIControl(const UIControl&);
	UIControl& operator=(const UIControl&);

public:
	UIControl();

	virtual Direction getMoveDirection(Game* game, Entity* entity) override;
	virtual bool isUser() const override;

	virtual ~UIControl();

};