#include "InterfaceText.h"
float InterfaceText::F_TEXT_HEIGHT_OFFSET = 2;


InterfaceText::InterfaceText()
{
	static bool isFontLoaded;
	static sf::Font font;

	if (!isFontLoaded) 
		isFontLoaded = font.loadFromFile("res/monofonto.ttf");

	fText.setCharacterSize(15);
	fText.setFont(font);
}

void InterfaceText::setText(const std::string &txt) 
{
	fText.setString(txt);
}

void InterfaceText::draw() const
{
	if(fVisible)
		Frame::getInstance().draw(fText, Frame::FrameLayer::Interface);
}

void InterfaceText::setPosition(const sf::Vector2f & p)
{
	fText.setPosition(p);
}

float InterfaceText::getWidth() const
{
	return fText.getGlobalBounds().width;
}

float InterfaceText::getHeight() const
{
	return fText.getGlobalBounds().height + F_TEXT_HEIGHT_OFFSET;
}



