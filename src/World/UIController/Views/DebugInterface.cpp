#include "DebugInterface.h"

DebugInterface::DebugInterface(UIInterface& f) : InterfaceView(f), fFrame(f.getFrame()), fDebugViewGroup(f, ViewAlignment::Right)
{
	fGroupList.push_back(&fDebugViewGroup);
}

void DebugInterface::update()
{
	InterfaceView::update();
	fDebugViewGroup.setPosition(sf::Vector2f(fFrame.getFrameWidth() - fDebugViewGroup.calculateWidth(), 0));
}