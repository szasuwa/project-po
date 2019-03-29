#pragma once
#include "Menu.h"
#include "../Frame.h"


class DebugMenu : public Menu
{
	int fFpsLastLength = 0;
	int fFpsLength = 0;
	sf::Text fFpsMeter;

public:
	DebugMenu();
	~DebugMenu();
	void drawMenu(sf::RenderWindow & window);
};

