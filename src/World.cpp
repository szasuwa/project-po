#include "World.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <windows.h>

int World::fNextGameObjectId;
std::vector<GameObject*> World::fGameObjects;
Player* World::fPlayerObject;
sf::Vector2f World::fOrigin;
float World::fWorldBoundaryLeft = 0;
float World::fWorldBoundaryRight = 1500;

World::World()
{
}


World::~World()
{
	unloadLevel();
}

void World::unloadLevel() {
	fOrigin.x = 0;
	destroyGameObjects();
}

void World::loadLevel(int id) {
	std::ifstream fs(F_LEVEL_FILENAME + std::to_string(id));
	if (!fs.fail()) {
		std::stringstream bf;
		bf << fs.rdbuf();
		bf >> fWorldBoundaryLeft;
		bf >> fWorldBoundaryRight;
		std::string temp = bf.str().erase(0, bf.str().find('\n') + 1);

		std::vector<Serializable *> * vect = fSerializationHandler.deserializeBundle(temp);
		unloadLevel();
		for (Serializable* obj : *vect) {
			addGameObject((GameObject*)obj);
		}
		delete vect;
		fs.close();
	}
}

const std::vector<GameObject *> World::getGameObjectList() {
	return fGameObjects;
}

void World::setPlayer(Player *player) {
	fPlayerObject = player;
}

GameObject* World::findGameObject(int id) {
	for (GameObject* object : fGameObjects) {
		if (object->getId() == id) {
			return object;
		}
	}
	return nullptr;
}

void World::addGameObject(GameObject* object) {
	fGameObjects.push_back(object);
}

void World::destroyGameObjects() {
	while (fGameObjects.size() > 0) {
		delete fGameObjects.back();
		fGameObjects.pop_back();
	}
}

int World::getNextGameObjectId() {
	++fNextGameObjectId;
	return fNextGameObjectId;
}

void World::scrollMap(float v) {
	fOrigin.x = std::max(fWorldBoundaryLeft, std::min(fOrigin.x + v, fWorldBoundaryRight - GameEngine::getWindowSize().x));
	
	for (GameObject* object : fGameObjects) {
		object->getTransformable()->setOrigin(fOrigin);
	}
}