#include "Menu.h"

sf::Font Menu::fFont;
bool Menu::fIsFontLoaded;

Menu::Menu()
{
	if (!fIsFontLoaded) {
		fIsFontLoaded = fFont.loadFromFile("res/monofonto.ttf");
	}
}


Menu::~Menu()
{
	
}
