#include "GraphicalUserInterface.h"

GraphicalUserInterface::GraphicalUserInterface() : fControlsViewGroup(ViewAlignment::Left), fInfoViewGroup(ViewAlignment::Left), fUserViewGroup(ViewAlignment::Left)
{
	fGroupList.push_back(&fControlsViewGroup);
	fGroupList.push_back(&fInfoViewGroup);
	fGroupList.push_back(&fUserViewGroup);
}

void GraphicalUserInterface::update(UIInterface& f)
{
	InterfaceView::update(f);

	fInfoViewGroup.setPosition(sf::Vector2f(0, 0));

	fUserViewGroup.setPosition(sf::Vector2f((f.getFrame().getFrameWidth() - fUserViewGroup.calculateWidth())/2, 0));

	fControlsViewGroup.setPosition(fInfoViewGroup.getPosition() + sf::Vector2f(0, fInfoViewGroup.calculateHeight()));
}