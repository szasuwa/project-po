#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window)
{
}

GameEngine::~GameEngine()
{
	for (GameObject* object : fGameObjects) {
		delete object;
	}
}

void GameEngine::initGame() 
{
	fPlayerObject = new Player(fGameWindow.getSize());
	fGameObjects.push_back(fPlayerObject);
}

void GameEngine::gameLoop()
{
	if (fGameWindow.isOpen()) {
		initGame();
	}
	
	while (fGameWindow.isOpen())
	{
		handleEvents();
		updateFrame();
	}
}

void GameEngine::updateFrame() {
	fGameWindow.clear();
	for (GameObject* object : fGameObjects) {
		object->update();
		fGameWindow.draw(*(*object).getDrawable());
	}
	fGameWindow.display();
}

void GameEngine::handleEvents() {
	sf::Event appEvent;
	while (fGameWindow.pollEvent(appEvent))
	{
		switch (appEvent.type)
		{
		case sf::Event::Closed:
			fGameWindow.close();
			break;
		default:
			break;
		}
	}
}

GameObject* GameEngine::findGameObject(int id) {
	for (GameObject* object : fGameObjects) {
		if (object->getId() == id) {
			return object;
		}
	}
	return nullptr;
}

void GameEngine::addGameObject(GameObject* object) {
	fGameObjects.push_back(object);
}

void GameEngine::destroyGameObject(GameObject* object) {
	for (int i = 0; i<fGameObjects.size(); ++i) {
		if (fGameObjects[i] == object) {
			fGameObjects.erase(fGameObjects.begin()+i);
			return;
		}
	}
}

void GameEngine::destroyGameObject(int id) {
	for (int i = 0; i < fGameObjects.size(); ++i) {
		if (fGameObjects[i]->getId() == id) {
			fGameObjects.erase(fGameObjects.begin() + i);
			return;
		}
	}
}