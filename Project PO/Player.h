#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Player : public GameObject
{
	const sf::Vector2u F_WINDOW_SIZE;

public:
	Player(const sf::Vector2u windowSize);
	~Player();
	void update();
};

