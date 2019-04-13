#include "InterfaceSeparator.h"

InterfaceSeparator::InterfaceSeparator(float h)
{
	fHeight = 5;
}

void InterfaceSeparator::draw() const
{
}

void InterfaceSeparator::setPosition(const sf::Vector2f & p)
{
}

float InterfaceSeparator::getWidth() const
{
	return 0;
}

float InterfaceSeparator::getHeight() const
{
	return fHeight;
}



