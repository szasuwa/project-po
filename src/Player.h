#pragma once
#include "PhysicalObject.h"
#include "WorldBoundaries.h"
#include "Frame.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class Player : public PhysicalObject
{
	//World
	sf::Vector2f fOrigin;
	static WorldBoundaries fWorldBoundaries;

	//Movement
	float fSpeed = 250.f;
	float fJumpForce = 500.f;
	float fScrollOffsetRight = 400.f;
	float fScrollOffsetLeft = 400.f;

	void controlMovement();
	void scrollMap(float v);

public:
	Player();
	~Player();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();

	static void setWorldBoundaries(WorldBoundaries b);
	
};

