#pragma once
class EntityController;

class EntityControllerFactory {
private:
	// copy constructor and assignment operator are disallowed
	EntityControllerFactory(const EntityControllerFactory&);
	EntityControllerFactory& operator=(const EntityControllerFactory&);

	// constructor and destructor are private
	EntityControllerFactory();
	~EntityControllerFactory();

public:
	static EntityControllerFactory* getInstance();
	EntityController* createFromChar(char c);
};