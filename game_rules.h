#pragma once

class Game;
class Entity;
class Position;

enum class GameResult {
	UNKNOWN, HERO_WINS, HERO_LOSES,
};

/*
	This is an interface class.

	A GameRules object determines which moves are legal,
	carries out legal moves, determines whether or not
	the game is over, and (if the game is over) determines
	if the hero won or lost.
*/
class GameRules {
private:
	// no copy constructor and assignmnet operator
	GameRules(const GameRules&);
	GameRules& operator=(const GameRules&);

public:
	GameRules();

	virtual bool allowMove(Game* game, Entity* actor, const Position& source, const Position& dest) const = 0;
	virtual void enactMove(Game* game, Entity* actor, const Position& dest) const = 0;
	virtual GameResult checkGameResult(Game* game) const = 0;

	virtual ~GameRules();
};
