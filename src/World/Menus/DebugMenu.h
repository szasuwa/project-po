#pragma once
#include "Menu.h"
#include "../Frame.h"


class DebugMenu : public Menu
{
	sf::Text fFpsMeter;

public:
	DebugMenu();
	~DebugMenu();
	void drawMenu(sf::RenderWindow & window);
};

