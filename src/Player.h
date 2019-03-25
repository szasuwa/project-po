#pragma once
#include "PhysicalObject.h"
#include "Frame.h"
#include "SerializationHandler.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class Player : public PhysicalObject
{
	//Movement
	float fSpeed = 250.f;
	float fJumpForce = 500.f;
	float fScrollOffsetRight = 400.f;
	float fScrollOffsetLeft = 400.f;

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

