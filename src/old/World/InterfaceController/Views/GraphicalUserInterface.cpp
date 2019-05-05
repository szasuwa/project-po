#include "GraphicalUserInterface.h"

GraphicalUserInterface::GraphicalUserInterface()
{
	fGroupList.push_back(&fControlsViewGroup);
	fGroupList.push_back(&fInfoViewGroup);
	fGroupList.push_back(&fUserViewGroup);
}

void GraphicalUserInterface::update()
{
	InterfaceView::update();

	Frame& frame = Frame::getInstance();

	fInfoViewGroup.setPosition(sf::Vector2f(0, 0));

	fUserViewGroup.setPosition(sf::Vector2f((frame.getFrameWidth() - fUserViewGroup.calculateWidth())/2, 0));

	fControlsViewGroup.setPosition(fInfoViewGroup.getPosition() + sf::Vector2f(0, fInfoViewGroup.calculateHeight()));
}