#include "Player.h"
#include "World.h"
#include <iostream>



Player::Player()
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
	getTransformable()->setPosition(GameEngine::getWindowSize().x / 2, GameEngine::getWindowSize().y / 2);
	World::setPlayer(this);
}

Player::~Player()
{
}

void Player::deserializeData(std::stringstream &ss) {
	PhysicalObject::deserializeData(ss);
}

void Player::serializeData(std::stringstream &ss, bool last) {
	ss << SERIALIZABLE_CLASS_TYPE_PLAYER << SERIALIZABLE_FIELD_DELIMITER;
	PhysicalObject::serializeData(ss, false);
	Serializable::serializeData(ss, last);
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

void Player::handleForces()
{
	PhysicalObject::handleForces();

	//Prevent escaping window boundaries
	sf::FloatRect bounds = getGlobalBounds();

	if (bounds.top + fForceVector.y*GameEngine::getFrameTime() < 0) {
		fCollisionSensor.triggerCollision(0, 0, 1, 0);
		fForceVector.y = -bounds.top;
	}

	if (bounds.top + bounds.height + fForceVector.y*GameEngine::getFrameTime() > GameEngine::getWindowSize().y) {
		fCollisionSensor.triggerCollision(0, 0, 0, 1);
		fForceVector.y = GameEngine::getWindowSize().y - bounds.top - bounds.height;
	}

	//Scrolling
	if (bounds.left + bounds.width + fForceVector.x*GameEngine::getFrameTime() > GameEngine::getWindowSize().x - fScrollOffsetRight) {
		World::scrollMap(bounds.left + bounds.width + fForceVector.x*GameEngine::getFrameTime() - GameEngine::getWindowSize().x + fScrollOffsetRight);
	}

	if (bounds.left < fScrollOffsetLeft) {
		World::scrollMap(bounds.left - fScrollOffsetLeft);
	}
}