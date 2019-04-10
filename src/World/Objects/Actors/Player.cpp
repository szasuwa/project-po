#include "Player.h"
#include "../../Map/Bases/Map.h"

int Player::fPoints = 0;

Player::Player(Map* map) : Player(sf::Vector2f(Frame::getWindowWidth() / 2, Frame::getWindowHeight() / 2), map)
{
}

Player::Player(sf::Vector2f position, Map* map) : PhysicalObject(true, true, map)
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

MapEditorItem *Player::getGhostDrawable() {
	MapEditorItem *out = new MapEditorItem();
	sf::RectangleShape *rs = new sf::RectangleShape(sf::Vector2f(10, 10));
	out->drawable = rs;
	out->transformable = rs;
	return out;
};

void Player::resize(sf::Vector2f rb, bool vLock, bool hLock, bool snapToGrid) {
	sf::RectangleShape *shape = (sf::RectangleShape*)fDrawable;
	sf::Transformable *transform = getTransformable();
	sf::Vector2f position = transform->getPosition();
	sf::Vector2f size = shape->getSize();

	if (!hLock) {
		size.x = rb.x - position.x;

		if (snapToGrid) {
			size.x = MapGrid::roundToGrid(size.x);
		}
	}

	if (!vLock) {
		size.y = rb.y - position.y;

		if (snapToGrid) {
			size.y = MapGrid::roundToGrid(size.y);
		}
	}

	shape->setSize(size);
}

sf::Transformable *Player::getTransformable() {
	return ((sf::Shape*)fDrawable);
};

void Player::update() 
{
	controlMovement();
	handleForces();
}

void Player::updateGuiInfo() {
	Gui::setPoints(fPoints);
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
		fMap->destroyGameObject(obj);
		addPoint();
		updateGuiInfo();
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
		fMap->scrollMap(bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() - Frame::getWindowWidth() + fScrollOffsetRight);
	}

	if (bounds.left < fScrollOffsetLeft) {
		fMap->scrollMap(bounds.left - fScrollOffsetLeft);
	}
}

void Player::addPoint(int p) {
	fPoints += p;
}

void Player::subPoint(int p) {
	fPoints -= p;
}

int Player::getPoints() {
	return fPoints;
}

void Player::setPoints(int p) {
	fPoints = p;
}