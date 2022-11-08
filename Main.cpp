#include <iostream>
#include <fstream>
#include "maze.h"

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

	std::unique_ptr<Maze> maze = Maze::read(in);
	
	std::cout << maze.get()->getHeight() << std::endl;
	std::cout << maze.get()->getWidth() << std::endl;

	std::cout << "made a maze" << std::endl;

	maze.get()->print();

}