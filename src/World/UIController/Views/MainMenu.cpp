#include "MainMenu.h"

MainMenu::MainMenu(UIInterface& f) : fMainMenuViewGroup(f)
{
	fGroupList.push_back(&fMainMenuViewGroup);
}

void MainMenu::update(UIInterface& f)
{
	InterfaceView::update(f);

	fMainMenuViewGroup.setPosition(sf::Vector2f((f.getFrame().getFrameWidth() - fMainMenuViewGroup.calculateWidth()), f.getFrame().getFrameHeight() - fMainMenuViewGroup.calculateHeight())/2.f);
}