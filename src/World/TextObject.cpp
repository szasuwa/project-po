#include "TextObject.h"

TextObject::TextObject() : TextObject("", 15)
{
}

TextObject::TextObject(const unsigned int& size) : TextObject("", size)
{
}

TextObject::TextObject(const std::string& text, const unsigned int & size)
{
	static bool isFontLoaded = false;
	static sf::Font font;

	if (!isFontLoaded)
		isFontLoaded = font.loadFromFile("res/neoletters.ttf");

	((sf::Texture&)font.getTexture(size)).setSmooth(false);
	
	setFont(font);
	setString(text);
	setCharacterSize(size);
	setColor(TEXT_DEFAULT_COLOR);
}

void TextObject::append(const std::string& text)
{
	setString(getString() + text);
}

void TextObject::removeLastCharacters(const unsigned int& count)
{
	std::string temp = getString();
	temp = temp.substr(0, temp.size() - count);
	setString(temp);
}