#include "TextViewItem.h"
float TextViewItem::F_TEXT_HEIGHT_OFFSET = 2;


TextViewItem::TextViewItem()
{
	static bool isFontLoaded;
	static sf::Font font;

	if (!isFontLoaded) 
		isFontLoaded = font.loadFromFile("res/monofonto.ttf");

	fText.setCharacterSize(15);
	fText.setFont(font);
}

void TextViewItem::setText(const std::string &txt)
{
	fText.setString(txt);
}

void TextViewItem::draw() const
{
	if(fVisible)
		Frame::getInstance().draw(fText, Frame::FrameLayer::Interface);
}

void TextViewItem::setPosition(const sf::Vector2f & p)
{
	fText.setPosition(p);
}

float TextViewItem::getWidth() const
{
	return fText.getGlobalBounds().width;
}

float TextViewItem::getHeight() const
{
	return fText.getGlobalBounds().height + F_TEXT_HEIGHT_OFFSET;
}



