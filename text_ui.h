#pragma once

#include "ui.h"
#include <string>
#include <iostream>
#include "maze.h"
#include "game.h"

/*
	A TextUI object implements the virtual functions of UI by
	printing to cout and reading from cin
*/
class TextUI : public UI {
private:
	Direction dir;
	std::string message;
	TextUI(const TextUI&);
	TextUI& operator=(const TextUI&);

public:
	TextUI();

	virtual Direction getMoveDirection() override;
	virtual void displayMessage(const std::string& msg, bool endgame) override;
	virtual void render(Game* game) override;

	virtual ~TextUI();
};