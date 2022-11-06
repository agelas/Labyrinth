#pragma once

#include "entity_controller.h"
#include "position.h"
#include <string>

class EntityController;

// Generic class representing a game entity (hero, minotaur, inaminate object, etc.)
// Is not intended to have derived classes.
class Entity {
private:
	std::string glyph;
	std::string properties;
	EntityController* controller;
	Position position;

	// Copy constructor and assignment operator are disallowed
	Entity(const Entity&);
	Entity& operator=(const Entity&);

public:
	Entity();
	
	void setGlyph(const std::string& glyph);
	void setProperties(const std::string& props);
	std::string getGlyph() const;
	std::string getProperties() const;
	bool hasProperty(char prop) const;
	void setController(EntityController* controller);
	EntityController* getController();
	void setPosition(const Position& pos);
	Position getPosition() const;

	~Entity();
};
