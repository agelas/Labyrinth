#pragma once

#include <string>
#include "position.h"

class Game;

class UI {
private:
	static UI* ui_instance;
	UI(const UI&);
	UI& operator=(const UI&);
	
public:
	UI();

	static UI* getInstance();
	virtual Direction getMoveDirection() = 0;
	virtual void displayMessage(const std::string& msg, bool endgame = false) = 0;
	virtual void render(Game* game) = 0;

	virtual ~UI();
};
