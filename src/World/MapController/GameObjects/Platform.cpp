#include "Platform.h"

Platform::Platform(Map * map): Platform(sf::Vector2f(), PLATFORM_SIZE, PLATFORM_COLOR, map)
{
}

Platform::Platform(const sf::Vector2f & position, Map * map) : Platform(position, PLATFORM_SIZE, PLATFORM_COLOR, map)
{
}

Platform::Platform(const sf::Vector2f& position, const sf::Color& color, Map* map) : Platform(position, PLATFORM_SIZE, color, map)
{
}

Platform::Platform(const sf::Vector2f & position, const sf::Vector2f & size, Map * map) : Platform(position, size, PLATFORM_COLOR, map)
{
}

Platform::Platform(const sf::Vector2f & position, const sf::Vector2f & size, const sf::Color & color, Map * map) : GameObject(map)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(position);
	((sf::RectangleShape*)fDrawable)->setSize(size);
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}

Platform::Platform(const Platform & obj) : GameObject(obj)
{
	fDrawable = new sf::RectangleShape();
	fTransformable = (sf::RectangleShape*)fDrawable;
	fTransformable->setPosition(obj.fTransformable->getPosition());
	((sf::RectangleShape*)fDrawable)->setSize(((sf::RectangleShape*)obj.fDrawable)->getSize());
	((sf::RectangleShape*)fDrawable)->setFillColor(((sf::RectangleShape*)obj.fDrawable)->getFillColor());
}

Platform::~Platform()
{
	fTransformable = nullptr;
}

void Platform::update()
{
}

void Platform::onFocus()
{
}

sf::FloatRect Platform::getGlobalBounds() const
{
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
}

void Platform::resize(const sf::Vector2f & p, bool gridSnap, bool vLock, bool hLock)
{
	sf::RectangleShape * shape = ((sf::RectangleShape*)fDrawable);
	sf::Vector2f position = fTransformable->getPosition();
	sf::Vector2f size = shape->getSize();

	if (!hLock)
		size.x = (gridSnap ? MapGrid::roundToGrid(p.x - position.x) : (p.x - position.x));

	if (!vLock)
		size.y = (gridSnap ? MapGrid::roundToGrid(p.y - position.y) : (p.y - position.y));

	shape->setSize(size);
}

void Platform::setColor(const sf::Color & c)
{
	((sf::RectangleShape*)fDrawable)->setFillColor(c);
}

GameObjectClassType Platform::getClassType() const
{
	return GameObjectClassType::PLATFORM;
}

void Platform::serializeObject(std::ostream & ss) const
{
	ss << (int)(getClassType()) << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeObject(ss);
	ss << ((sf::RectangleShape *)fDrawable)->getSize().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getSize().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getFillColor().toInteger() << SERIALIZABLE_FIELD_DELIMITER;
}

void Platform::deserializeObject(std::istream & ss)
{
	GameObject::deserializeObject(ss);
	float x, y;
	ss >> x;
	ss >> y;
	sf::Uint32 c;
	ss >> c;
	((sf::RectangleShape *)fDrawable)->setSize(sf::Vector2f(x, y));
	((sf::RectangleShape *)fDrawable)->setFillColor(sf::Color(c));
}