#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>

#include "../Bases/PhysicalObject.h"
#include "../../Levels/WorldBoundaries.h"
#include "../../Frame.h"


class Player : public PhysicalObject
{
	//Movement
	float fSpeed = 250.f;
	float fJumpForce = 500.f;
	float fScrollOffsetRight = 400.f;
	float fScrollOffsetLeft = 400.f;

	int fPoints = 0;

	void controlMovement();
	void checkCollision(GameObject* obj);

public:
	Player(Level* lvl = nullptr);
	Player(sf::Vector2f position, Level* lvl = nullptr);
	~Player();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);
	CLASS_TYPE getClassType();

	sf::FloatRect getGlobalBounds();
	sf::Transformable *getTransformable();
	void update();	

	void addPoint();
	void subPoint();
	int getPoints();
	void setPoints(int p);
};

