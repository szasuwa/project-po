#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window), fFrame(Frame::getInstance()), fKeyController(KeyController::getInstance())
{
	fFrame.setWindow(fGameWindow);
}

void GameEngine::initGame()
{
	fGameWindow.setFramerateLimit(120);
	Map * map = fMapManager.load("map1");
	fMapManager.save("map2", *map);
	
	fInterface.updateView();
	fInterface.addInterface(InterfaceController::InterfaceType::Debug);
	fInterface.addInterface(InterfaceController::InterfaceType::Info);
	fInterface.addInterface(InterfaceController::InterfaceType::MapEditor);
	fInterface.addInterface(InterfaceController::InterfaceType::User);
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
			fGameWindow.clear();
			fInterface.update();
			fInterface.draw();
			fMapManager.updateMap();
			fMapManager.drawMap();
			fGameWindow.display();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long)(fFrame.getMaxFrameTime() * 1000)));
		}
		fFrame.nextFrame();
	}
}

void GameEngine::handleEvents() {
	sf::Event appEvent;
	while (fGameWindow.pollEvent(appEvent))
	{
		switch (appEvent.type)
		{
		case sf::Event::KeyPressed:
			/*
			if (!fIsDebugKeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
				fIsDebugKeyPressed = true;
				fDisplayDebug = !fDisplayDebug;
			}

			if (!fIsEditKeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2)) {
				fIsEditKeyPressed = true;
				fIsEditingMap = !fIsEditingMap;
			}
			*/
			break;

		case sf::Event::KeyReleased:
			/*
			if (fIsDebugKeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
				fIsDebugKeyPressed = false;
			}

			if (fIsEditKeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2)) {
				fIsEditKeyPressed = false;
			}
			*/
			break;

		case sf::Event::GainedFocus:
			fFrame.nextFrame();
			break;

		case sf::Event::Resized:
			fInterface.updateView();
			fFrame.nextFrame();
			fMapManager.updateCamera();
			break;

		case sf::Event::Closed:
			fGameWindow.close();
			break;

		default:
			break;
		}
	}
}