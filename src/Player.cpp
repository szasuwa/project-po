#include "Player.h"
#include "World.h"

Player::Player() : PhysicalObject(true, true)
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
	getTransformable()->setPosition(Frame::getWindowWidth() / 2, Frame::getWindowHeight() / 2);
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
		fForceVector.x -= fSpeed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		fForceVector.x += fSpeed;
	}
	fForceVector.x = std::max(-fSpeed, std::min(fSpeed, fForceVector.x));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fCollisionSensor.getBottom())
	{
		fForceVector.y = -fJumpForce;
	}

	//Scrolling
	sf::FloatRect bounds = getGlobalBounds();

	if ((bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() > Frame::getWindowWidth() - fScrollOffsetRight)) {
		World::scrollMap(bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() - Frame::getWindowWidth() + fScrollOffsetRight);
	}

	if (bounds.left < fScrollOffsetLeft) {
		World::scrollMap(bounds.left - fScrollOffsetLeft);
	}
}