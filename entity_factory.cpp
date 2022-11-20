#include "entity_factory.h"

EntityControllerFactory::EntityControllerFactory() {}

EntityControllerFactory::~EntityControllerFactory() {}

EntityControllerFactory* EntityControllerFactory::getInstance() {
	/*
		Get a pointer to the singleton instance of EntityControllerFactory
	*/
	static EntityControllerFactory entityControllerFactoryInstance;
	return &entityControllerFactoryInstance;
}

EntityController* EntityControllerFactory::createFromChar(char c) {
	switch (c) {
	case 'u':
		return new UIControl();
	case 'c':
		return new SimpleChaser();
	}
	throw std::runtime_error("Unknown character supplied to EntityController Factory");
}