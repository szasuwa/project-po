#include "InterfaceGroup.h"


InterfaceGroup::InterfaceGroup(const Alignment &a):fAlignment(a)
{
}

void InterfaceGroup::drawGroup() const 
{
	if (!fVisible)
		return;

	for (InterfaceItem * item : fItemList) 
	{
		if (item != nullptr) 
		{
			item->draw();
		}
	}
}

float InterfaceGroup::calculateHeight() const 
{
	float out = 0;
	for (InterfaceItem * item : fItemList) 
	{
		if (item != nullptr && item->getVisibility()) 
		{
			out += item->getHeight();
		}
	}
	return out;
}

float InterfaceGroup::calculateWidth() const 
{
	float out = 0;
	for (InterfaceItem * item : fItemList) {
		if (item != nullptr && item->getVisibility()) 
		{
			out = std::max(out, item->getWidth());
		}
	}
	return out;
}

void InterfaceGroup::calculatePositions(float offset) 
{
	Frame & frame = Frame::getInstance();

	for (InterfaceItem * item : fItemList) 
	{
		if (item != nullptr && item->getVisibility()) 
		{
			switch (fAlignment)
			{
				case InterfaceGroup::Alignment::Left:
					item->setPosition(sf::Vector2f(fMargin.left, offset + fMargin.top));
					break;
				case InterfaceGroup::Alignment::Right:
					item->setPosition(sf::Vector2f(frame.getFrameWidth() - item->getWidth() - fMargin.right, offset + fMargin.top));
					break;
				case InterfaceGroup::Alignment::Center:
					item->setPosition(sf::Vector2f((frame.getFrameWidth() - item->getWidth())/2, offset + fMargin.top));
					break;
				default:
					break;
			}
			
			offset += item->getHeight();
		}
	}
}

bool InterfaceGroup::getVisibility() const 
{
	return fVisible;
}

void InterfaceGroup::setVisibility(const bool & v) 
{
	fVisible = v;
}

void InterfaceGroup::toggleVisibility()
{
	fVisible = !fVisible;
}


InterfaceGroup::Alignment InterfaceGroup::getAlignment() const
{
	return fAlignment;
}

void InterfaceGroup::setAlignment(const Alignment & v) 
{
	fAlignment = v;
}

