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
	fFpsMeter.setString(std::to_string(Frame::getFrameRate()) +" FPS");
	fFpsLength = fFpsMeter.getString().getSize();
	if (fFpsLastLength != fFpsLength) {
		fFpsLastLength = fFpsLength;
		fFpsMeter.setPosition(sf::Vector2f(Frame::getWindowWidth() - fFpsMeter.getLocalBounds().width, 0));
	}
	window.draw(fFpsMeter);
}