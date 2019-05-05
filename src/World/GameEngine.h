#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Interfaces/FrameInterface.h"
#include "Interfaces/InputInterface.h"
#include "Interfaces/MapInterface.h"
#include "Interfaces/UIInterface.h"
#include "UIController/InterfaceType.h"
#include "InputController/KeyBindingIndex.h"

class GameEngine
{
	FrameInterface & fFrame;
	InputInterface & fInput;
	MapInterface& fMapController;
	UIInterface& fUiController;

	bool fTimeFlowEnabled = true;

	void initGame();
	void handleTriggers();
	void handleEvents();

public:
	GameEngine(FrameInterface& f, InputInterface& i, MapInterface& m, UIInterface& u);

	void gameLoop();
};