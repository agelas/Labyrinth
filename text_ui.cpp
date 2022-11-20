#include "text_ui.h"

TextUI::TextUI() {
	this->dir = Direction::NONE;
}

TextUI::~TextUI() {}

Direction TextUI::getMoveDirection() {
	char move;
	bool valid = false; // Default false

	while (!valid) {
		std::cout << "Your move (w/a/s/d): ";
		std::cin >> move;

		switch (move) {
		case 'w':
			this->dir = Direction::UP;
			valid = true;
			break;
		case 'a':
			this->dir = Direction::LEFT;
			valid = true;
			break;
		case 's':
			this->dir = Direction::DOWN;
			valid = true;
			break;
		case 'd':
			this->dir = Direction::RIGHT;
			valid = true;
			break;
		default:
			std::cout << "Unknown direction" << std::endl;
			this->dir = Direction::NONE;
			valid = false;
			break;
		}
	}
	return this->dir;
}

void TextUI::displayMessage(const std::string& msg, bool) {
	/*
		Assign the message field to inputted message
	*/
	this->message = msg;
}

void TextUI::render(Game* game) {
	Maze& m = game->getMaze();
	Entity* e;

	for (int i = 0; i < m.getHeight(); i++) {
		for (int j = 0; j < m.getWidth(); j++) {
			Position p = Position(j, i);
			e = game->getEntityAt(p);
			if (e) {
				std::cout << e->getGlyph();
			}
			else {
				std::cout << (m.getTile(p))->getGlyph();
			}
		}
		std::cout << std::endl;
	}
	if (message != "") { // Check if there is a message waiting to be printed
		std::cout << message << std::endl;
		message = "";
	}
}