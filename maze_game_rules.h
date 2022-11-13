#pragma once

#include "game_rules.h"
#include "game.h"

class MazeGameRules : public GameRules {
private:
	MazeGameRules(const MazeGameRules&);
	MazeGameRules& operator=(const MazeGameRules&);

public:
	MazeGameRules();

	virtual bool allowMove(Game* game, Entity* actor, const Position& source, const Position& dest) const override;
	virtual void enactMove(Game* game, Entity* actor, const Position& dest) const override;
	virtual GameResult checkGameResult(Game* game) const override;
	const Position inanimateDestination(const Position& source, const Position& dest) const;

	virtual ~MazeGameRules();
};