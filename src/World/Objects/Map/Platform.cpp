#include "Platform.h"

Platform::Platform(Level* lvl) : Platform(sf::Vector2f(10, 10), sf::Vector2f(0, 0), sf::Color(255, 255, 255, 255), lvl)
{
}

Platform::Platform(sf::Vector2f position, Level* lvl) : Platform(sf::Vector2f(20, 5), position, sf::Color(255, 255, 255, 255), lvl)
{
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, Level* lvl) : Platform(size, position, sf::Color(255,255,255,255), lvl)
{
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Color color, Level* lvl) : GameObject(lvl)
{
	fDrawable = new sf::RectangleShape(size);
	((sf::RectangleShape*)fDrawable)->setPosition(position);
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}

Platform::~Platform()
{
}

void Platform::deserializeData(std::stringstream &ss) {
	GameObject::deserializeData(ss);
	float x, y;
	sf::Uint32 c;
	ss >> x;
	ss >> y;
	((sf::RectangleShape *)fDrawable)->setSize(sf::Vector2f(x, y));
	ss >> c;
	((sf::RectangleShape *)fDrawable)->setFillColor(sf::Color(c));
}

void Platform::serializeData(std::stringstream &ss, bool last)
{
	ss << CLASS_TYPE::PLATFORM << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeData(ss, false);
	ss << ((sf::RectangleShape *)fDrawable)->getSize().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getSize().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getFillColor().toInteger();
	Serializable::serializeData(ss, last);

}

Platform::CLASS_TYPE Platform::getClassType() {
	return CLASS_TYPE::PLATFORM;
}

sf::FloatRect Platform::getGlobalBounds() {
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
};

MapEditorItem *Platform::getGhostDrawable() {
	MapEditorItem *out = new MapEditorItem();
	sf::RectangleShape *rs = new sf::RectangleShape(sf::Vector2f(20, 5));
	rs->setFillColor(sf::Color(255, 255, 255, 255));
	out->drawable = rs;
	out->transformable = rs;
	return out;
};


void Platform::resize(sf::Vector2f rb, bool vLock, bool hLock) {
	sf::RectangleShape *shape = (sf::RectangleShape*)fDrawable;
	sf::Transformable *transform = getTransformable();
	sf::Vector2f position = transform->getPosition();
	sf::Vector2f size = shape->getSize();

	if (!hLock) {
		size.x = rb.x - position.x;
	}

	if (!vLock) {
		rb.y - position.y;
	}

	shape->setSize(size);
}


sf::Transformable *Platform::getTransformable() {
	return ((sf::Shape*)fDrawable);
};

void Platform::update()
{
}

void Platform::handleCollision(GameObject *collider) {
}

sf::Vector2f Platform::getSize() 
{
	return ((sf::RectangleShape*)fDrawable)->getSize();
}

void Platform::setSize(sf::Vector2f &size) 
{
	((sf::RectangleShape*)fDrawable)->setSize(size);
}

sf::Vector2f Platform::getPosition() 
{
	return ((sf::RectangleShape*)fDrawable)->getPosition();
}

void Platform::setPosition(sf::Vector2f &position) 
{
	((sf::RectangleShape*)fDrawable)->setPosition(position);
}

void Platform::setColor(sf::Color color) {
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}
