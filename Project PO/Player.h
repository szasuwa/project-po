#pragma once
#include "PhysicalObject.h"
#include "GameEngine.h"
#include "SerializationHandler.h"
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

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();
};

