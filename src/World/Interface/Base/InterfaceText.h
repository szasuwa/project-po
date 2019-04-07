#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "InterfaceItem.h"


class InterfaceText : public InterfaceItem {
	static float F_TEXT_HEIGHT_OFFSET;
	sf::Text fText;

protected:
	static sf::Font fFont;
	static bool fIsFontLoaded;

public:
	InterfaceText();
	void setText(std::string &txt);
	sf::Drawable * getDrawable();
	void setPosition(sf::Vector2f &pos);
	float getWidth();
	float getHeight();
};