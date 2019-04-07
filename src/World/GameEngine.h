#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Frame.h"
#include "Levels/Level.h"
#include "Levels/LevelLoader.h"
#include "Levels/MapEditor.h"
#include "Levels/MapEditorItem.h"
#include "Interface/Base/InterfaceController.h"
#include "Interface/DebugInterface.h"
#include "Interface/InfoInterface.h"
#include "Interface/MapEditorInterface.h"
#include "Interface/Gui.h"


class GameEngine
{
	sf::RenderWindow &fGameWindow;
	Level * fActiveLevel;
	std::vector<Level *> fLevelList;
	LevelLoader fLevelLoader;
	InterfaceController fInterface;
	DebugInterface fDebugInterface;
	InfoInterface fInfoInterface;
	MapEditorInterface fMapEditorInterface;
	Gui fGui;
	MapEditor fEditor;
	
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

