#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <thread> 
#include <chrono>

#include "Interfaces/FrameInterface.h"
#include "Interfaces/InputInterface.h"
#include "Interfaces/MapInterface.h"

class GameEngine
{
	FrameInterface & fFrame;
	InputInterface & fInput;
	MapInterface& fMapController;
	//UiControllerInterface & fUiController;
	//MapControllerInterface & fMapController;

	void initGame();
	void handleTriggers();
	void handleEvents();

public:
	//GameEngine(FrameInterface & f, InputInterface & i, UiControllerInterface & u, MapControllerInterface & m);
	GameEngine(FrameInterface& f, InputInterface& i, MapInterface& m);

	void gameLoop();
};