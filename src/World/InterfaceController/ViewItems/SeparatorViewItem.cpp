#include "SeparatorViewItem.h"

SeparatorViewItem::SeparatorViewItem(float h)
{
	fHeight = 5;
}

void SeparatorViewItem::draw() const
{
}

void SeparatorViewItem::setPosition(const sf::Vector2f & p)
{
}

float SeparatorViewItem::getWidth() const
{
	return 0;
}

float SeparatorViewItem::getHeight() const
{
	return fHeight;
}



