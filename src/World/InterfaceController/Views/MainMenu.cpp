#include "MainMenu.h"

MainMenu::MainMenu()
{
	fGroupList.push_back(&fMainMenuViewGroup);
}

void MainMenu::update()
{
	InterfaceView::update();

	Frame& frame = Frame::getInstance();

	fMainMenuViewGroup.setPosition(sf::Vector2f((frame.getFrameWidth() - fMainMenuViewGroup.calculateWidth()), frame.getFrameHeight() - fMainMenuViewGroup.calculateHeight())/2.f);
}