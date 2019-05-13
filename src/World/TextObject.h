#pragma once
#include <SFML/Graphics/Text.hpp>

#include "../GameConstants.h"


class TextObject : public sf::Text {
public:
	TextObject();
	TextObject(const unsigned int& size);
	TextObject(const std::string & text, const unsigned int & size);
	void append(const std::string& text);
	void removeLastCharacters(const unsigned int & count = 1);
};