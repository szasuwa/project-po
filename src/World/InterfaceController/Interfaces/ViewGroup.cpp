#include "ViewGroup.h"


ViewGroup::ViewGroup() : ViewGroup(ViewAlignment::Left)
{
}

ViewGroup::ViewGroup(const ViewAlignment& a) : fPosition(sf::Vector2f()), fVisible(true), fAlignment(a)
{
}

void ViewGroup::draw() const
{
	if (!fVisible)
		return;

	for (ViewItem* item : fItemList)
	{
		if (item != nullptr) 
		{
			item->draw();
		}
	}
}

sf::Vector2f ViewGroup::getPosition() const
{
	return fPosition;
}

void ViewGroup::setPosition(const sf::Vector2f& p)
{
	fPosition = p;
}


float ViewGroup::calculateHeight() const 
{
	float out = 0;
	for (ViewItem* item : fItemList)
	{
		if (item != nullptr && item->getVisibility()) 
		{
			out += item->getHeight();
		}
	}
	return out;
}

float ViewGroup::calculateWidth() const 
{
	float out = 0;
	for (ViewItem* item : fItemList) {
		if (item != nullptr && item->getVisibility()) 
		{
			out = std::max(out, item->getWidth());
		}
	}
	return out;
}

void ViewGroup::calculatePositions()
{
	float offset = 0;
	float width = calculateWidth();
	Frame & frame = Frame::getInstance();

	for (ViewItem* item : fItemList)
	{
		if (item != nullptr && item->getVisibility()) 
		{
			switch (fAlignment)
			{
				case ViewAlignment::Left:
					item->setPosition(sf::Vector2f(fPosition.x, offset + fPosition.y));
					break;

				case ViewAlignment::Center:
					item->setPosition(sf::Vector2f(fPosition.x + (width - item->getWidth())/2, offset + fPosition.y));
					break;

				case ViewAlignment::Right:
					item->setPosition(sf::Vector2f(fPosition.x + (width - item->getWidth()), offset + fPosition.y));
					break;

				default:
					break;
			}			
			offset += item->getHeight();
		}
	}
}

bool ViewGroup::getVisibility() const 
{
	return fVisible;
}

void ViewGroup::setVisibility(const bool & v) 
{
	fVisible = v;
}

void ViewGroup::toggleVisibility()
{
	fVisible = !fVisible;
}

ViewAlignment ViewGroup::getAlignment() const
{
	return fAlignment;
}

void ViewGroup::setAlignment(const ViewAlignment& a)
{
	fAlignment = a;
}