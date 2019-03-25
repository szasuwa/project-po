#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <Windows.h>
#include "Frame.h"
#include "WorldLoader.h"
#include "DebugMenu.h"

class GameEngine
{
	sf::RenderWindow &fGameWindow;
	WorldLoader fWorldLoader;
	DebugMenu fDebugMenu;

	bool fDisplayDebug = false;
	bool fIsDebugKeyPressed = false;
	
	void initGame();
	void handleEvents();
	void updateFrame();
public:
	

	GameEngine(sf::RenderWindow &window);
	~GameEngine();

	void gameLoop();
};

