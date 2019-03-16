#include "Platform.h"

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
