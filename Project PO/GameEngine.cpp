#include "GameEngine.h"


sf::Vector2u GameEngine::F_WINDOW_SIZE;
sf::Clock GameEngine::fClk;
double GameEngine::fLastFrameTime = 0;
const double GameEngine::F_MAX_FRAME_TIME = 1.0 / 120.0;

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window)
{
	F_WINDOW_SIZE = fGameWindow.getSize();
	fWorld = new World();
}

GameEngine::~GameEngine()
{
	delete fWorld;
}

void GameEngine::initGame() 
{
	fGameWindow.setFramerateLimit(120);
	fWorld->loadDevLevel();
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
	for (GameObject* object : World::getGameObjectList())
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
			case sf::Event::Closed:
				fGameWindow.close();
				break;

			default:
				break;
		}
	}
}

 const sf::Vector2u GameEngine::getWindowSize() {
	return F_WINDOW_SIZE;
}
