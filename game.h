#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "maze.h"
#include "entity.h"
#include "position.h"
#include "ui.h"

class Maze;
class Position;
class Entity;
class UI;
class GameRules;

// Encapsulates the entirety of the game state and 
// coordinates the overall gamplay.
class Game {

using EntityVec = std::vector<Entity*>;

private:
	std::unique_ptr<Maze> maze;
	EntityVec evec;

public:
	Game();

	void setMaze(std::unique_ptr<Maze> maze);
	std::unique_ptr<Maze> getMaze();
	void setUI(UI *ui);
	UI* getUI();
	void setGameRules(GameRules *gameRules);
	GameRules* getGameRules();
	void addEntity(Entity* entity);
	Entity* getEntityAt(const Position& pos);
	const EntityVec& getEntities() const;
	EntityVec getEntitiesWithProperty(char prop) const;
	void gameLoop();
	void takeTurn(Entity* actor);
	static Game* loadGame(std::istream& in);

	~Game();
};