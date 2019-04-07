#include "InterfaceText.h"
sf::Font InterfaceText::fFont;
bool InterfaceText::fIsFontLoaded;
float InterfaceText::F_TEXT_HEIGHT_OFFSET = 2;

InterfaceText::InterfaceText()
{
	if (!fIsFontLoaded) {
		fIsFontLoaded = fFont.loadFromFile("res/monofonto.ttf");
	}
	fText.setCharacterSize(15);
	fText.setFont(fFont);
}

void InterfaceText::setText(std::string &txt) {
	fText.setString(txt);
}

sf::Drawable * InterfaceText::getDrawable() {
	return &fText;
}

void InterfaceText::setPosition(sf::Vector2f &pos) {
	fText.setPosition(pos);
}

float InterfaceText::getWidth() {
	return fText.getGlobalBounds().width;
}

float InterfaceText::getHeight() {
	return fText.getGlobalBounds().height + F_TEXT_HEIGHT_OFFSET;
}