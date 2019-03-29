#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window)
{
	Frame::setWindowSize(fGameWindow.getSize());
}

GameEngine::~GameEngine()
{
	for (size_t i = 0; i < fLevelList.size(); ++i) {
		if (fLevelList[i] != nullptr) {
			delete fLevelList[i];
		}
	}
}

void GameEngine::initGame() 
{
	fGameWindow.setFramerateLimit(120);
	fLevelList.push_back(fLevelLoader.loadLevel(1));
	fActiveLevel = fLevelList[0];
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
			std::this_thread::sleep_for(std::chrono::milliseconds((long)(Frame::getMaxFrameTime() * 1000)));
		}
		Frame::nextFrame();
	}
}

void GameEngine::updateFrame() 
{
	fGameWindow.clear();
	if (fDisplayDebug) {
		fDebugMenu.drawMenu(fGameWindow);
	}

	if (fActiveLevel != nullptr) {
		fActiveLevel->broadcastUpdate();
		fActiveLevel->broadcastDraw(fGameWindow);
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