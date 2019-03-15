#include "Player.h"

Player::Player(const sf::Vector2u windowSize) : F_WINDOW_SIZE(windowSize)
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
	fPositionVector.x = 0;
	fPositionVector.y = 0;
}

Player::~Player()
{
}

void Player::update() 
{
	controlMovement();
	controlGravity();
	applyMovement();
}

void Player::controlGravity()
{
	fMovementVector.y += fGravityAcceleration;
	fMovementVector.y = std::min(fMovementVector.y, fGravityForce);
}

void Player::hitGround() 
{
	fIsJumping = false;
}

void Player::controlMovement()
{
	//Reset movement vector
	fMovementVector.x = 0;

	//Check movement keys
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		fMovementVector.x -= fSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		fMovementVector.x += fSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !fIsJumping)
	{
		fIsJumping = true;
		fMovementVector.y = fJumpForce;
	}
}

void Player::applyMovement() 
{
	//Set position vector
	fPositionVector.x += fMovementVector.x;
	fPositionVector.y += fMovementVector.y;

	//Prevent escaping window boundaries
	fPositionVector.x = std::max(0.0f, std::min(fPositionVector.x, F_WINDOW_SIZE.x - ((sf::RectangleShape*)fDrawable)->getSize().x));
	fPositionVector.y = std::max(0.0f, std::min(fPositionVector.y, F_WINDOW_SIZE.y - ((sf::RectangleShape*)fDrawable)->getSize().y));

	//Set position
	((sf::RectangleShape*)fDrawable)->setPosition(fPositionVector);
}