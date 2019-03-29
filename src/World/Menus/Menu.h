#pragma once
#include <SFML/Graphics.hpp>


class Menu
{
protected:
	static sf::Font fFont;
	static bool fIsFontLoaded;

public:
	Menu();
	~Menu();

	virtual void drawMenu(sf::RenderWindow &window) = 0;
};

