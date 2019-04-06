#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Levels/Level.h"
#include "Frame.h"
#include "Levels/LevelLoader.h"
#include "Menus/DebugMenu.h"
#include "Menus/Gui.h"
#include "Levels/MapEditor.h"
#include "Levels/MapEditorItem.h"


class GameEngine
{
	sf::RenderWindow &fGameWindow;
	Level * fActiveLevel;
	std::vector<Level *> fLevelList;
	LevelLoader fLevelLoader;
	DebugMenu fDebugMenu;
	MapEditor fEditor;
	Gui fGui;
	
	bool fIsEditingLevel = false;
	bool fIsEditKeyPressed = false;

	bool fDisplayDebug = false;
	bool fIsDebugKeyPressed = false;
	
	void initGame();
	void handleEvents();
	void drawFrame();
	void updateFrame();

public:
	GameEngine(sf::RenderWindow &window);
	~GameEngine();

	void gameLoop();
};

