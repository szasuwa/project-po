#pragma once
#include "PhysicalObject.h"
#include "GameEngine.h"
#include "SerializationHandler.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class Player : public PhysicalObject
{
	//Movement
	float fSpeed = 250.f;
	float fJumpForce = 500.f;
	float fScrollOffsetRight = 300.f;
	float fScrollOffsetLeft = 300.f;

	void controlMovement();

public:
	Player();
	~Player();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();
	void handleForces();
};

