#include "World.h"
#include "GameObject.h"
#include "Player.h"
#include <iostream>
#include <windows.h>

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
	destroyGameObjects();
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

	std::cout << fSerializationHandler.serializeBundle((Serializable **)fGameObjects.data(), fGameObjects.size()) << std::endl;
}

void World::loadLevel(int id) {
	std::ifstream fs(F_LEVEL_FILENAME + std::to_string(id));
	if (!fs.fail()) {
		std::stringstream bf;
		bf << fs.rdbuf();
		std::string temp = bf.str();
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