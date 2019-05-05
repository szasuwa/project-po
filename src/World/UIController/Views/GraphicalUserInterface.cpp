#include "GraphicalUserInterface.h"

GraphicalUserInterface::GraphicalUserInterface(UIInterface& f) : InterfaceView(f), fFrame(f.getFrame()), fControlsViewGroup(f), fInfoViewGroup(f), fUserViewGroup(f)
{
	fGroupList.push_back(&fControlsViewGroup);
	fGroupList.push_back(&fInfoViewGroup);
	fGroupList.push_back(&fUserViewGroup);
}

void GraphicalUserInterface::update()
{
	InterfaceView::update();

	fInfoViewGroup.setPosition(sf::Vector2f(0, 0));

	fUserViewGroup.setPosition(sf::Vector2f((fFrame.getFrameWidth() - fUserViewGroup.calculateWidth())/2, 0));

	fControlsViewGroup.setPosition(fInfoViewGroup.getPosition() + sf::Vector2f(0, fInfoViewGroup.calculateHeight()));
}