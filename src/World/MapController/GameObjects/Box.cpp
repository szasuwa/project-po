#include "Box.h"


Box::Box(Map* map) : Box(sf::Vector2f(), BOX_SIZE, BOX_COLOR, map)
{
}

Box::Box(const sf::Vector2f& position, Map* map) : Box(position, BOX_SIZE, BOX_COLOR, map)
{
}

Box::Box(const sf::Vector2f& position, const sf::Color& color, Map* map) : Box(position, BOX_SIZE, color, map)
{
}

Box::Box(const sf::Vector2f& position, const sf::Vector2f& size, Map* map) : Box(position, size, BOX_COLOR, map)
{
}

Box::Box(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, Map* map) : DynamicObject(map)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::RectangleShape*)fDrawable)->setSize(size);
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}

Box::Box(const Box& obj) : DynamicObject(obj)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::RectangleShape*)fDrawable)->setSize(((sf::RectangleShape*)obj.fDrawable)->getSize());
	((sf::RectangleShape*)fDrawable)->setFillColor(((sf::RectangleShape*)obj.fDrawable)->getFillColor());
}

sf::Vector2f Box::onTrigger(const sf::Vector2f& p, GameObject* obj, const Collision& c, const sf::FloatRect& z, const sf::FloatRect& o)
{
	return p;
}

void Box::onUpdate(GameEngineInterface& f)
{
	DynamicObject::onUpdate(f);
}

void Box::onFocus(GameEngineInterface& f)
{
}

sf::FloatRect Box::getGlobalBounds() const
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void Box::resize(const sf::Vector2f& p, bool gridSnap, bool vLock, bool hLock)
{
	sf::RectangleShape* shape = ((sf::RectangleShape*)fDrawable);
	sf::Vector2f position = fTransformable->getPosition();
	sf::Vector2f size = shape->getSize();

	if (!hLock)
		size.x = (gridSnap ? MapGrid::roundToGrid(p.x - position.x) : (p.x - position.x));

	if (!vLock)
		size.y = (gridSnap ? MapGrid::roundToGrid(p.y - position.y) : (p.y - position.y));

	shape->setSize(size);
}

void Box::setColor(const sf::Color & c)
{
	((sf::Shape*)fDrawable)->setFillColor(c);
}

GameObjectClassType Box::getClassType() const
{
	return GameObjectClassType::BOX;
}

void Box::serializeObject(std::ostream & ss) const
{
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	DynamicObject::serializeObject(ss);
	ss << ((sf::RectangleShape*)fDrawable)->getSize().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape*)fDrawable)->getSize().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape*)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
}

void Box::deserializeObject(std::istream & ss)
{
	DynamicObject::deserializeObject(ss);

	float x, y;
	sf::Uint32 c;

	if (!(ss >> x >> y >> c))
		return;

	((sf::RectangleShape*)fDrawable)->setSize(sf::Vector2f(x, y));
	((sf::RectangleShape*)fDrawable)->setFillColor(sf::Color(c));
}

bool Box::checkSerializableValidity(const std::string & s)
{
	return std::regex_match(s, std::regex(
		REGEX_WHITESPACE
		+ F_REGEX_GAME_OBJECT_PATTERN
		+ F_REGEX_DYNAMIC_OBJECT_PATTERN
		+ REGEX_FLOAT_PATTERN + "{2}"
		+ REGEX_INT_PATTERN + "{1}"
		+ REGEX_WHITESPACE
	));
}