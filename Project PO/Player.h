#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <algorithm>

class Player : public GameObject
{
	const sf::Vector2u F_WINDOW_SIZE;
	//Movement
	sf::Vector2f fPositionVector;
	sf::Vector2f fMovementVector;
	int fSpeed = 1;
	float fGravityAcceleration = 0.05f;
	float fGravityForce = 5.0f;
	bool fIsJumping = false;
	float fJumpForce = -2.0f;

	void controlMovement();
	void controlGravity();
	void applyMovement();
	void hitGround();

public:
	Player(const sf::Vector2u windowSize);
	~Player();
	void update();
};

