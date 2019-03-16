#pragma once
#include "PhysicalObject.h"
#include "GameEngine.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class Player : public PhysicalObject
{
	//Movement
	static float fSpeed;
	static float fJumpForce;

	void controlMovement();

public:
	Player();
	~Player();
	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();
};

