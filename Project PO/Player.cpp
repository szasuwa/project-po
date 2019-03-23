#include "Player.h"
#include <iostream>

float Player::fSpeed = 250.f;
float Player::fJumpForce = 500.f;

Player::Player()
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
	getTransformable()->setPosition(GameEngine::getWindowSize().x / 2, GameEngine::getWindowSize().y / 2);
}

Player::~Player()
{
}

sf::FloatRect Player::getGlobalBounds() {
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
};

sf::Transformable *Player::getTransformable() {
	return ((sf::Shape*)fDrawable);
};

void Player::update() 
{
	controlMovement();
	handleForces();
}

void Player::controlMovement()
{
	//Check movement keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		fForceVector.x = -fSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		fForceVector.x = fSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fCollisionSensor.getBottom())
	{
		fForceVector.y = -fJumpForce;
	}
}