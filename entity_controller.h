#pragma once

#include "position.h"

// Forward declare Game and Entity

class EntityController {
private:
	EntityController(const EntityController&);
	EntityController& operator=(const EntityController&);

public:
	EntityController();

	//virtual Direction getMoveDirection(Game* game, Entity* entity) = 0;
	virtual bool isUser() const = 0;

	virtual ~EntityController();
};
