#include <iostream>
#include <fstream>
#include "game.h"
#include "text_ui.h"
#include "maze_game_rules.h"

int main(int argc, char *argv[]) {
	const char* filename;
	if (argc < 2) {
		std::cerr << "Error: Need filename" << std::endl;
		return 1;
	}
	filename = argv[1];
	std::cout << filename << std::endl;
	std::ifstream in(filename);

	if (!in.is_open()) {
		std::cerr << "Error: Could not open maze file" << std::endl;
		return 1;
	}

	Game* game = Game::loadGame(in);
	game->setGameRules(new MazeGameRules());
	game->setUI(new TextUI());
	std::cout << "New Game Created" << std::endl;
	game->gameLoop();
}