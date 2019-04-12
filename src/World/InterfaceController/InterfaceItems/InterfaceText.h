#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "InterfaceItem.h"


class InterfaceText : public InterfaceItem {
	static float F_TEXT_HEIGHT_OFFSET;
	sf::Text fText;

public:
	InterfaceText();
	void setText(const std::string &txt);
	virtual const sf::Drawable & getDrawable() const;
	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};