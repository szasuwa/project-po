#include "MainMenu.h"

MainMenu::MainMenu(UIInterface& f) : InterfaceView(f), fFrame(f.getFrame()), fMainMenuViewGroup(f)
{
	fGroupList.push_back(&fMainMenuViewGroup);
}

void MainMenu::update()
{
	InterfaceView::update();

	fMainMenuViewGroup.setPosition(sf::Vector2f((fFrame.getFrameWidth() - fMainMenuViewGroup.calculateWidth()), fFrame.getFrameHeight() - fMainMenuViewGroup.calculateHeight())/2.f);
}