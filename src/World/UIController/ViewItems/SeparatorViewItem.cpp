#include "SeparatorViewItem.h"

SeparatorViewItem::SeparatorViewItem(float h)
{
	fHeight = h;
}

void SeparatorViewItem::update(UIInterface& f)
{
}

void SeparatorViewItem::draw(UIInterface& f) const
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



