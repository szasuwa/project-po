#include "Player.h"
#include "Level.h"

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
		fLevel->scrollMap(bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() - Frame::getWindowWidth() + fScrollOffsetRight);
	}

	if (bounds.left < fScrollOffsetLeft) {
		fLevel->scrollMap(bounds.left - fScrollOffsetLeft);
	}
}