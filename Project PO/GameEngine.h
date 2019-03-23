#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class World;

class GameEngine
{
	sf::RenderWindow &fGameWindow;
	World* fWorld;
	
	static sf::Vector2u F_WINDOW_SIZE;
	static const double F_MAX_FRAME_TIME;

	static sf::Clock fClk;
	static double fLastFrameTime;
	
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

