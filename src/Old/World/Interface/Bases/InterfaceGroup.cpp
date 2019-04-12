#include "InterfaceGroup.h"

void InterfaceGroup::drawGroup(sf::RenderWindow &window) {
	if (fVisible) {
		for (InterfaceItem * item : fItemList) {
			if (item != nullptr && item->getVisibility()) {
				window.draw(*(item->getDrawable()));
			}
		}
	}
}

float InterfaceGroup::calculateHeight() {
	float out = 0;
	for (InterfaceItem * item : fItemList) {
		if (item != nullptr && item->getVisibility()) {
			out += item->getHeight();
		}
	}
	return out;
}

float InterfaceGroup::calculateWidth() {
	float out = 0;
	for (InterfaceItem * item : fItemList) {
		if (item != nullptr && item->getVisibility()) {
			out = std::max(out, item->getWidth());
		}
	}
	return out;
}

void InterfaceGroup::calculatePositions(float offset) {
	for (InterfaceItem * item : fItemList) {
		if (item != nullptr && item->getVisibility()) {
			switch (fAlignment)
			{
			case InterfaceGroup::Left:
				item->setPosition(sf::Vector2f(fMarginLeft, offset + fMarginTop));
				break;
			case InterfaceGroup::Right:
				item->setPosition(sf::Vector2f(Frame::getWindowWidth() - item->getWidth() - fMarginRight, offset + fMarginTop));
				break;
			case InterfaceGroup::Center:
				item->setPosition(sf::Vector2f((Frame::getWindowWidth() - item->getWidth())/2, offset + fMarginTop));
				break;
			default:
				break;
			}
			
			offset += item->getHeight();
		}
	}
}

bool InterfaceGroup::getVisibility() {
	return fVisible;
}

void InterfaceGroup::setVisibility(bool v) {
	fVisible = v;
}

InterfaceGroup::Alignment InterfaceGroup::getAlignment() {
	return fAlignment;
}

void InterfaceGroup::setAlignment(Alignment v) {
	fAlignment = v;
}