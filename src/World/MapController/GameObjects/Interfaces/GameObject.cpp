#include "GameObject.h"
const std::string GameObject::F_REGEX_GAME_OBJECT_PATTERN = REGEX_INT_PATTERN + "{1}" + REGEX_FLOAT_PATTERN + "{2}" + REGEX_BOOL_PATTERN + "{2}";


GameObject::GameObject(Map * map) : fMap(map)
{
}

GameObject::GameObject(const GameObject & obj) 
{
	fId = obj.fId;
	fMap = obj.fMap;
	fHasCollider = obj.fHasCollider;
	fHasTrigger = obj.fHasTrigger;
}

GameObject::~GameObject()
{
	delete fDrawable;
	delete fTransformable;
}

bool GameObject::onCollision(GameObject* obj)
{
	return true;
}

bool GameObject::onTrigger(GameObject* obj)
{
	return true;
}

void GameObject::draw() const 
{
	if (fDrawable == nullptr)
		return;

	Frame::getInstance().draw(*fDrawable, Frame::FrameLayer::MapArea);
}

int GameObject::getId() const 
{
	return fId;
}

void GameObject::setId(const int& id)
{
	fId = id;
}

void GameObject::setMap(Map * map) 
{
	fMap = map;
}

bool GameObject::hasCollider() const
{
	return fHasCollider;
}

bool GameObject::hasTrigger() const
{
	return fHasTrigger;
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

void GameObject::move(const sf::Vector2f & p)
{
	if (fTransformable == nullptr)
		return;

	fTransformable->move(p);
}

void GameObject::serializeObject(std::ostream & ss) const 
{
	if (fTransformable == nullptr)
		return;

	ss << fId << SERIALIZABLE_FIELD_DELIMITER;
	ss << fTransformable->getPosition().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fTransformable->getPosition().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fHasCollider << SERIALIZABLE_FIELD_DELIMITER;
	ss << fHasTrigger << SERIALIZABLE_FIELD_DELIMITER;
}

void GameObject::deserializeObject(std::istream & ss) 
{
	if (fTransformable == nullptr)
		return;

	ss >> fId;
	float x, y;
	ss >> x;
	ss >> y;
	fTransformable->setPosition(x,y);
	ss >> fHasCollider;
	ss >> fHasTrigger;
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
