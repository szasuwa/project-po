#pragma once
#include <SFML/Window/Event.hpp>

class TextWatcherInterface {
public:
	virtual ~TextWatcherInterface() {};
	virtual void onTextInput(sf::Event::TextEvent text) = 0;
};