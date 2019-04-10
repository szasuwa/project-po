#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Frame.h"
#include "Map/Bases/Map.h"
#include "Map/Manager/MapManager.h"
#include "Map/Editor/MapEditor.h"
#include "Map/Editor/MapEditorItem.h"
#include "Interface/Bases/InterfaceController.h"
#include "Interface/DebugInterface.h"
#include "Interface/InfoInterface.h"
#include "Interface/MapEditorInterface.h"
#include "Interface/Gui.h"


class GameEngine
{
	sf::RenderWindow &fGameWindow;
	Map * fActiveMap;
	MapManager fMapManager;
	InterfaceController fInterface;
	DebugInterface fDebugInterface;
	InfoInterface fInfoInterface;
	MapEditorInterface fMapEditorInterface;
	Gui fGui;
	MapEditor fEditor;
	
	bool fIsEditingMap = false;
	bool fIsEditKeyPressed = false;

	bool fDisplayDebug = false;
	bool fIsDebugKeyPressed = false;
	
	void initGame();
	void handleEvents();
	void drawFrame();
	void updateFrame();

public:
	GameEngine(sf::RenderWindow &window);

	void gameLoop();
};

