#include "World.h"
#include "GameObject.h"
#include "Player.h"

int World::fNextGameObjectId;
std::vector<GameObject*> World::fGameObjects;
Player* World::fPlayerObject;

World::World()
{
}


World::~World()
{
	unloadLevel();
}

void World::unloadLevel() {
	for (GameObject* object : fGameObjects) {
		if (object != nullptr) {
			delete object;
		}		
	}
}

void World::loadDevLevel() {
	fPlayerObject = new Player();
	addGameObject(fPlayerObject);
	GameObject* obj = new Platform(sf::Vector2f(GameEngine::getWindowSize().x, 5), sf::Vector2f(0, GameEngine::getWindowSize().y - 5), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
	obj = new Platform(sf::Vector2f(100, 5), sf::Vector2f(350, GameEngine::getWindowSize().y - 19), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
	obj = new Platform(sf::Vector2f(GameEngine::getWindowSize().x / 4, 5), sf::Vector2f(0, GameEngine::getWindowSize().y - 65), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
	obj = new Platform(sf::Vector2f(GameEngine::getWindowSize().x / 8, 5), sf::Vector2f(0, GameEngine::getWindowSize().y - 95), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
}

const std::vector<GameObject *> World::getGameObjectList() {
	return fGameObjects;
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

void World::destroyGameObject(GameObject* object) {
	for (int i = 0; i < fGameObjects.size(); ++i) {
		if (fGameObjects[i] == object) {
			fGameObjects.erase(fGameObjects.begin() + i);
			return;
		}
	}
}

void World::destroyGameObject(int id) {
	for (int i = 0; i < fGameObjects.size(); ++i) {
		if (fGameObjects[i]->getId() == id) {
			fGameObjects.erase(fGameObjects.begin() + i);
			return;
		}
	}
}

int World::getNextGameObjectId() {
	++fNextGameObjectId;
	return fNextGameObjectId;
}