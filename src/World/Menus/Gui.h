#pragma once 
#include "Menu.h"


class Gui : public Menu {
	sf::Text fPointsBox;
	static int fPoints;

public:
	Gui();
	~Gui();

	void drawMenu(sf::RenderWindow & window);
	static void setPoints(int p);
};