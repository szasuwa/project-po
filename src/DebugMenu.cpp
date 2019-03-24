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
	fFpsMeter.setString(std::to_string((int)(1.f / GameEngine::getFrameTime())) + "FPS");
	window.draw(fFpsMeter);
}