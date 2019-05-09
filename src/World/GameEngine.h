#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Interfaces/GameEngineInterface.h"
#include "Interfaces/FrameInterface.h"
#include "Interfaces/InputInterface.h"
#include "Interfaces/MapInterface.h"
#include "Interfaces/UIInterface.h"
#include "UIController/InterfaceType.h"
#include "InputController/KeyBindingIndex.h"
#include "UIController/ViewProperties.h"

class GameEngine : public GameEngineInterface
{
	bool fTimeFlowEnabled = true;

	void initGame();
	void handleTriggers();
	void handleEvents();

public:
	GameEngine(FrameInterface& f, InputInterface& i, MapInterface& m, UIInterface& u);

	void gameLoop();
};