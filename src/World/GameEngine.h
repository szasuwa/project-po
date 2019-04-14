#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Frame/Frame.h"
#include "KeyboardController/KeyController.h"
#include "InterfaceController/InterfaceController.h"
#include "MapController/MapController.h"

class GameEngine
{
	sf::RenderWindow &fGameWindow;
	Frame &fFrame;
	KeyController &fKeyController;
	InterfaceController fInterface;
	MapController fMapController;

	bool fIsEditingMap = false;
	bool fTimeFlowEnabled = true;

	void initGame();
	void handleTriggers();
	void handleEvents();

public:
	GameEngine(sf::RenderWindow &window);

	void gameLoop();
};