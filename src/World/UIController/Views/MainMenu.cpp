#include "MainMenu.h"

MainMenu::MainMenu(GameEngineInterface& f) : fMainMenuViewGroup(f)
{
	fGroupList.push_back(&fMainMenuViewGroup);
}

void MainMenu::update(GameEngineInterface& f)
{
	InterfaceView::update(f);

	fMainMenuViewGroup.setPosition(sf::Vector2f((f.getFrameInterface().getFrameWidth() - fMainMenuViewGroup.calculateWidth()), f.getFrameInterface().getFrameHeight() - fMainMenuViewGroup.calculateHeight())/2.f);
}