#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window)
{
	Frame::setWindowSize(fGameWindow.getSize());
	fWorld = new World();
	fDebugMenu = new DebugMenu();
}

GameEngine::~GameEngine()
{
	delete fDebugMenu;
	delete fWorld;
}

void GameEngine::initGame() 
{
	fGameWindow.setFramerateLimit(120);
	fWorld->loadLevel(1);
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
		else
		{
			Sleep(Frame::getMaxFrameTime() * 1000);
		}
		Frame::nextFrame();
	}
}

void GameEngine::updateFrame() 
{
	fGameWindow.clear();
	if (fDisplayDebug) {
		fDebugMenu->drawMenu(fGameWindow);
	}

	for (GameObject* object : World::getGameObjectList())
	{
		if (object == nullptr)
			continue;
		
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
			case sf::Event::KeyPressed:
				if (!fIsDebugKeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
					fIsDebugKeyPressed = true;
					fDisplayDebug = !fDisplayDebug;
				}
				break;

			case sf::Event::KeyReleased:
				if (fIsDebugKeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
					fIsDebugKeyPressed = false;
				}
				break;

			case sf::Event::GainedFocus:
				Frame::nextFrame();
				break;	

			case sf::Event::Resized:
				Frame::nextFrame();
				break;

			case sf::Event::Closed:
				fGameWindow.close();
				break;

			default:
				break;
		}
	}
}