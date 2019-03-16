#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"

class GameObject;
class Player;

class GameEngine
{
	sf::RenderWindow &fGameWindow;
	static sf::Clock fClk;
	static double fLastFrameTime;
	
	static int fNextGameObjectId;
	static std::vector<GameObject*> fGameObjects;
	static Player* fPlayerObject;

	void initGame();
	void handleEvents();
	void updateFrame();
public:
	static sf::Vector2u F_WINDOW_SIZE;

	GameEngine(sf::RenderWindow &window);
	~GameEngine();

	void gameLoop();
	static float getFrameTime();
	//GameObjects
	static int getNextGameObjectId();
	static const std::vector<GameObject*> getGameObjectList();
	//static GameObject* findGameObject(int id);
	static void addGameObject(GameObject* object);
	static void destroyGameObject(GameObject* object);
	static void destroyGameObject(int id);
};

