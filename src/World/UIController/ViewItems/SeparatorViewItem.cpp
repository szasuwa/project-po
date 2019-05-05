#include "SeparatorViewItem.h"

SeparatorViewItem::SeparatorViewItem(UIInterface& f, float h) : ViewItem(f)
{
	fHeight = h;
}

void SeparatorViewItem::update()
{
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



