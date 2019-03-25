#include "Player.h"

WorldBoundaries Player::fWorldBoundaries;

Player::Player() : PhysicalObject(true, true)
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10, 10));
	getTransformable()->setPosition(Frame::getWindowWidth() / 2, Frame::getWindowHeight() / 2);
	fOrigin.x = 0;
	fOrigin.y = 0;
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fCollider.isBottom())
	{
		fForceVector.y = -fJumpForce;
	}

	//Scrolling
	sf::FloatRect bounds = getGlobalBounds();

	if ((bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() > Frame::getWindowWidth() - fScrollOffsetRight)) {
		scrollMap(bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() - Frame::getWindowWidth() + fScrollOffsetRight);
	}

	if (bounds.left < fScrollOffsetLeft) {
		scrollMap(bounds.left - fScrollOffsetLeft);
	}
}

void Player::scrollMap(float v) {
	fOrigin.x = std::max(fWorldBoundaries.left, std::min(fOrigin.x + v, fWorldBoundaries.right - Frame::getWindowWidth()));
	GameObject::broadcastOriginChange(fOrigin);
}

void Player::setWorldBoundaries(WorldBoundaries b) {
	fWorldBoundaries = b;
}