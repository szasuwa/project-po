#include "Gui.h"

int Gui::fPoints = 0;

Gui::Gui()
{
	fPointsBox.setFont(fFont);
	fPointsBox.setCharacterSize(12);
	fPointsBox.setFillColor(sf::Color::White);
}

Gui::~Gui()
{
}

void Gui::drawMenu(sf::RenderWindow & window){
	fPointsBox.setString("Points: " + std::to_string(fPoints));
	window.draw(fPointsBox);
}

void Gui::setPoints(int p) {
	fPoints = p;
}