#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window), fEditor(nullptr, window)
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
	fEditor.setLevel(fActiveLevel);
	fDebugInterface.setAlignment(InterfaceGroup::Alignment::Right);
	fInfoInterface.setAlignment(InterfaceGroup::Alignment::Left);
	fMapEditorInterface.setAlignment(InterfaceGroup::Alignment::Left);
	fGui.setAlignment(InterfaceGroup::Alignment::Center);
	fInterface.addGroup(&fDebugInterface);
	fInterface.addGroup(&fInfoInterface);
	fInterface.addGroup(&fMapEditorInterface);
	fInterface.addGroup(&fGui);
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
			if (!fIsEditingLevel) {
				updateFrame();
			}
			else {
				fEditor.handleEditorControls();
			}
			drawFrame();
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
	fActiveLevel->broadcastUpdate();
}

void GameEngine::drawFrame()
{
	fGameWindow.clear();
	
	fDebugInterface.setVisibility(fDisplayDebug);
	fMapEditorInterface.setVisibility(fIsEditingLevel);

	fInterface.update();
	fInterface.draw(fGameWindow);

	if (fActiveLevel != nullptr) {
		fActiveLevel->broadcastDraw(fGameWindow);
	}

	if (fIsEditingLevel) {
		MapEditorItem *fEditorGhost;
		fEditorGhost = fEditor.getGhost();
		if (fEditorGhost != nullptr) {
			fGameWindow.draw(*fEditorGhost->drawable);
		}
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

				if (!fIsEditKeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2)) {
					fIsEditKeyPressed = true;
					fIsEditingLevel = !fIsEditingLevel;
				}
				break;

			case sf::Event::KeyReleased:
				if (fIsDebugKeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F3)) {
					fIsDebugKeyPressed = false;
				}

				if (fIsEditKeyPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2)) {
					fIsEditKeyPressed = false;
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