#include "Player.h"
#include "Level.h"
#include <iostream>

Player::Player(Level* lvl) : Player(sf::Vector2f(Frame::getWindowWidth() / 2, Frame::getWindowHeight() / 2), lvl)
{
}

Player::Player(sf::Vector2f position, Level* lvl) : PhysicalObject(true, true, lvl)
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
	getTransformable()->setPosition(position);
}

Player::~Player()
{
}

void Player::deserializeData(std::stringstream &ss) {
	PhysicalObject::deserializeData(ss);
}

void Player::serializeData(std::stringstream &ss, bool last) {
	ss << CLASS_TYPE::PLAYER << SERIALIZABLE_FIELD_DELIMITER;
	PhysicalObject::serializeData(ss, false);
	Serializable::serializeData(ss, last);
}

Player::CLASS_TYPE Player::getClassType() {
	return CLASS_TYPE::PLAYER;
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

void Player::checkCollision(GameObject* obj) {
	PhysicalObject::checkCollision(obj);

	if (obj == this)
		return;

	sf::FloatRect cBounds = getGlobalBounds();
	sf::FloatRect oBounds = obj->getGlobalBounds();

	if (!cBounds.intersects(oBounds))
		return;

	if(obj->getClassType() == CLASS_TYPE::POINT) {
		fLevel->destroyGameObject(obj);
		addPoint();
	}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fCollider.isBottom())
	{
		fForceVector.y = -fJumpForce;
	}

	//Scrolling
	sf::FloatRect bounds = getGlobalBounds();

	if ((bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() > Frame::getWindowWidth() - fScrollOffsetRight)) {
		fLevel->scrollMap(bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() - Frame::getWindowWidth() + fScrollOffsetRight);
	}

	if (bounds.left < fScrollOffsetLeft) {
		fLevel->scrollMap(bounds.left - fScrollOffsetLeft);
	}
}

void Player::addPoint() {
	++fPoints;
}

void Player::subPoint() {
	--fPoints;
}

int Player::getPoints() {
	return fPoints;
}

void Player::setPoints(int p) {
	fPoints = p;
}