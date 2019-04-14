#include "GameObject.h"

GameObject::GameObject(Map * map) : fMap(map)
{
}

GameObject::GameObject(const GameObject & obj) 
{
	fMap = obj.fMap;
}

GameObject::~GameObject()
{
	delete fDrawable;
	delete fTransformable;
}

void GameObject::draw() const 
{
	if (fDrawable == nullptr)
		return;

	Frame::getInstance().draw(*fDrawable, Frame::FrameLayer::MapArea);
}

void GameObject::setMap(Map * map) 
{
	fMap = map;
}

bool GameObject::hasCollider()
{
	return fHasCollider;
}

sf::Vector2f GameObject::getPosition() const
{
	if (fTransformable == nullptr)
		return sf::Vector2f();

	return fTransformable->getPosition();
}

void GameObject::setPosition(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
	if (fTransformable == nullptr)
		return;

	sf::Vector2f pos = fTransformable->getPosition();

	if (!vLock)
		pos.y = (gridSnap ? MapGrid::roundToGrid(p.y) : p.y);

	if (!hLock)
		pos.x = (gridSnap ? MapGrid::roundToGrid(p.x) : p.x);
	

	fTransformable->setPosition(pos);
}

void GameObject::move(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
	if (fTransformable == nullptr)
		return;

	sf::Vector2f pos = fTransformable->getPosition();

	if (!vLock)
		pos.y += p.y;

	if (!hLock)
		pos.x += p.x;

	setPosition(pos, gridSnap, vLock, hLock);
}

void GameObject::serializeObject(std::ostream & ss) const 
{
	if (fTransformable == nullptr)
		return;

	ss << fTransformable->getPosition().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fTransformable->getPosition().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fHasCollider << SERIALIZABLE_FIELD_DELIMITER;
}

void GameObject::deserializeObject(std::istream & ss) 
{
	if (fTransformable == nullptr)
		return;

	float x, y;
	ss >> x;
	ss >> y;
	fTransformable->setPosition(x,y);
	ss >> fHasCollider;
}

std::ostream & operator<<(std::ostream & s, const GameObject & o)
{
	o.serializeObject(s);
	return s;
}

std::istream & operator>>(std::istream & s, GameObject & o)
{
	o.deserializeObject(s);
	return s;
}
