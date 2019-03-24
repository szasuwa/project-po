#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <Windows.h>

class World;
class DebugMenu;

class GameEngine
{
	sf::RenderWindow &fGameWindow;
	World* fWorld;
	DebugMenu* fDebugMenu;

	static sf::Vector2u F_WINDOW_SIZE;
	static const double F_MAX_FRAME_TIME;

	static sf::Clock fClk;
	static double fLastFrameTime;

	bool fDisplayDebug = false;
	bool fIsDebugKeyPressed = false;
	
	void initGame();
	void handleEvents();
	void updateFrame();
public:
	

	GameEngine(sf::RenderWindow &window);
	~GameEngine();

	void gameLoop();
	static float getFrameTime();
	static const sf::Vector2u getWindowSize();
};

