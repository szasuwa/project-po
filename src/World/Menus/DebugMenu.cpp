#include "DebugMenu.h"



DebugMenu::DebugMenu()
{
	fFpsMeter.setFont(fFont);
	fFpsMeter.setCharacterSize(12);
	fFpsMeter.setFillColor(sf::Color::White);
}


DebugMenu::~DebugMenu()
{
}

void DebugMenu::drawMenu(sf::RenderWindow &window) {
	fFpsMeter.setString(std::to_string(Frame::getFrameRate()) +"FPS");
	window.draw(fFpsMeter);
}