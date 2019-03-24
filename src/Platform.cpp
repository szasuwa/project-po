#include "Platform.h"
#include <iostream>
Platform::Platform()
{
	fDrawable = new sf::RectangleShape();
}

Platform::Platform(sf::Vector2f &position)
{
	fDrawable = new sf::RectangleShape(sf::Vector2f(10,10));
	((sf::RectangleShape*)fDrawable)->setPosition(position);
}

Platform::Platform(sf::Vector2f &size, sf::Vector2f &position)
{
	fDrawable = new sf::RectangleShape(size);
	((sf::RectangleShape*)fDrawable)->setPosition(position);
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position)
{
	fDrawable = new sf::RectangleShape(size);
	((sf::RectangleShape*)fDrawable)->setPosition(position);
}

Platform::Platform(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
	fDrawable = new sf::RectangleShape(size);
	((sf::RectangleShape*)fDrawable)->setPosition(position);
	((sf::RectangleShape*)fDrawable)->setFillColor(color);
}

Platform::~Platform()
{
}

int Platform::getClassType() {
	return 0;
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
	ss << SERIALIZABLE_CLASS_TYPE_PLATFORM << SERIALIZABLE_FIELD_DELIMITER;
	GameObject::serializeData(ss, false);
	ss << ((sf::RectangleShape *)fDrawable)->getSize().x << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getSize().y << SERIALIZABLE_FIELD_DELIMITER;
	ss << ((sf::RectangleShape *)fDrawable)->getFillColor().toInteger();
	Serializable::serializeData(ss, last);

}

sf::FloatRect Platform::getGlobalBounds() {
	return ((sf::Shape*)fDrawable)->getGlobalBounds();
};

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
