#include "entity.h"

Entity::Entity() {
	this->glyph = "";
	this->properties = "";
	this->controller = NULL;
	this->position = Position();
}

void Entity::setGlyph(const std::string& glyph) {
	this->glyph = glyph;
}

void Entity::setProperties(const std::string& props) {
	this->properties = props;
}

std::string Entity::getGlyph() const {
	return this->glyph;
}

std::string Entity::getProperties() const {
	return this->properties;
}

bool Entity::hasProperty(char prop) const {
	return properties.find(prop) != std::string::npos;
}

void Entity::setController(EntityController* controller) {
	this->controller = controller;
}

EntityController* Entity::getController() {
	return this->controller;
}

void Entity::setPosition(const Position& pos) {
	this->position = position;
}

Position Entity::getPosition() const{
	return this->position;
}

Entity::~Entity() {
	delete this->controller;
}