#include "GameEngine.h"
#include "GameObject.h"
#include "Player.h"

int GameEngine::fNextGameObjectId;
std::vector<GameObject*> GameEngine::fGameObjects;
sf::Vector2u GameEngine::F_WINDOW_SIZE;
Player* GameEngine::fPlayerObject;
sf::Clock GameEngine::fClk;
double GameEngine::fLastFrameTime = 0;
const double GameEngine::F_MAX_FRAME_TIME = 1.0 / 120.0;

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window)
{
	F_WINDOW_SIZE = fGameWindow.getSize();
}

GameEngine::~GameEngine()
{
	for (GameObject* object : fGameObjects) {
		delete object;
	}
}

void GameEngine::initGame() 
{
	fGameWindow.setFramerateLimit(120);
	fPlayerObject = new Player();
	addGameObject(fPlayerObject);
	GameObject* obj = new Platform(sf::Vector2f(fGameWindow.getSize().x,5), sf::Vector2f(0, fGameWindow.getSize().y-5), sf::Color(125,125,125,255));
	addGameObject(obj);
	obj = new Platform(sf::Vector2f(100, 5), sf::Vector2f(350, fGameWindow.getSize().y - 19), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
	obj = new Platform(sf::Vector2f(fGameWindow.getSize().x/4, 5), sf::Vector2f(0, fGameWindow.getSize().y - 65), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
	obj = new Platform(sf::Vector2f(fGameWindow.getSize().x/8, 5), sf::Vector2f(0, fGameWindow.getSize().y - 95), sf::Color(125, 125, 125, 255));
	addGameObject(obj);
}

void GameEngine::gameLoop()
{
	if (fGameWindow.isOpen()) {
		initGame();
	}
	
	while (fGameWindow.isOpen())
	{
		handleEvents();
		if (fGameWindow.hasFocus()) {

			updateFrame();
		}		
		fLastFrameTime = fClk.restart().asSeconds();
	}
}

float GameEngine::getFrameTime() {
	return std::min(fLastFrameTime, F_MAX_FRAME_TIME);
}

void GameEngine::updateFrame() 
{
	fGameWindow.clear();
	for (GameObject* object : fGameObjects)
	{
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
			case sf::Event::GainedFocus:
				fLastFrameTime = F_MAX_FRAME_TIME;
				fClk.restart();
				break;	

			case sf::Event::Resized:
				fLastFrameTime = F_MAX_FRAME_TIME;
				fClk.restart();
				break;

			case sf::Event::Closed:
				fGameWindow.close();
				break;

			default:
				break;
		}
	}
}

const std::vector<GameObject *> GameEngine::getGameObjectList() {
	return fGameObjects;
}

/*
GameObject* GameEngine::findGameObject(int id) {
	for (GameObject* object : fGameObjects) {
		if (object->getId() == id) {
			return object;
		}
	}
	return nullptr;
}
*/

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

int GameEngine::getNextGameObjectId() {
	++fNextGameObjectId;
	return fNextGameObjectId;
}