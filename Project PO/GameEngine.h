#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameObject.h"
#include "Player.h"
#include <iostream>

class GameEngine
{
	sf::RenderWindow &fGameWindow;
	std::vector<GameObject*> fGameObjects;
	Player* fPlayerObject;

	void initGame();
	void handleEvents();
	void updateFrame();
public:
	GameEngine(sf::RenderWindow &window);
	~GameEngine();

	void gameLoop();
	//GameObjects
	GameObject* findGameObject(int id);
	void addGameObject(GameObject* object);
	void destroyGameObject(GameObject* object);
	void destroyGameObject(int id);
};

