#include "Point.h"
#include "../Maps/Map.h"


Point::Point(Map* map) : Point(sf::Vector2f(), POINT_RADIUS, POINT_COLOR, map)
{
}

Point::Point(const sf::Vector2f &position, Map* map) : Point(sf::Vector2f(), POINT_RADIUS, POINT_COLOR, map)
{
}

Point::Point(const sf::Vector2f & position, const float & radius, Map * map) : Point(position, radius, POINT_COLOR, map)
{
}

Point::Point(const sf::Vector2f & position, const sf::Color & color, Map * map) : Point(position, 5, POINT_COLOR, map)
{
}

Point::Point(const sf::Vector2f & position, const float & radius, const sf::Color & color, Map * map) : GameObject(map)
{
	fHasTrigger = true;
	fHasCollider = false;
	fDrawable = new sf::CircleShape();
	fTransformable = (sf::CircleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::CircleShape*)fDrawable)->setRadius(radius);
	((sf::CircleShape*)fDrawable)->setFillColor(color);
}

Point::Point(const Point & obj) : GameObject(obj)
{
	fDrawable = new sf::CircleShape();
	fTransformable = (sf::CircleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::CircleShape*)fDrawable)->setRadius(((sf::CircleShape*)obj.fDrawable)->getRadius());
	((sf::CircleShape*)fDrawable)->setFillColor(((sf::CircleShape*)obj.fDrawable)->getFillColor());
}

void Point::onUpdate(GameEngineInterface& f)
{
}

void Point::onFocus(GameEngineInterface& f)
{
}

bool Point::onTrigger(GameObject * o)
{
	if (o == this || o == nullptr)
		return true;

	if (o->getClassType() == GameObjectClassType::PLAYER) {
		fMap->destroyGameObject(this);
		return false;
	}
	return false;
}

sf::FloatRect Point::getGlobalBounds() const 
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void Point::resize(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
	sf::CircleShape *shape = (sf::CircleShape*)fDrawable;
	sf::Vector2f pos = fTransformable->getPosition();
	float radius = shape->getRadius();
	pos.x -= radius / 2;
	pos.y += radius / 2;

	if (hLock) 
	{
		radius = p.y - pos.y;
		radius = (gridSnap ? std::abs(MapGrid::roundToGrid(p.y) - MapGrid::roundToGrid(pos.y)) : std::abs(p.y - pos.y));
	} else if(vLock) 
	{
		radius = (gridSnap ? std::abs(MapGrid::roundToGrid(p.x) - MapGrid::roundToGrid(pos.x)) : std::abs(p.x - pos.x));
	}
	else 
	{
		radius = std::max((gridSnap ? MapGrid::roundToGrid(p.y) - MapGrid::roundToGrid(pos.y) : p.y - pos.y), 
			(gridSnap ? MapGrid::roundToGrid(p.x) - MapGrid::roundToGrid(pos.x) : p.x - pos.x));
	}

	shape->setRadius(radius);
}

void Point::setColor(const sf::Color & c) {
	((sf::Shape*)fDrawable)->setFillColor(sf::Color(c));
}

GameObjectClassType Point::getClassType() const
{
	return GameObjectClassType::POINT;
}

void Point::serializeObject(std::ostream & ss) const {
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeObject(ss);
	ss << ((sf::CircleShape*)fDrawable)->getRadius() << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::CircleShape*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
}

void Point::deserializeObject(std::istream & ss) {
	GameObject::deserializeObject(ss);
    float r;
    ss >> r;
	sf::Uint32 c;
	ss >> c;
    ((sf::CircleShape*)fDrawable)->setRadius(r);
	((sf::CircleShape*)fDrawable)->setFillColor(sf::Color(c));
}

bool Point::checkSerializableValidity(const std::string& s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ REGEX_FLOAT_PATTERN + "{1}"
		+ REGEX_INT_PATTERN + "{1}"
		+ REGEX_WHITESPACE
	));
}