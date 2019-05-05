#include "DebugInterface.h"

DebugInterface::DebugInterface() : fDebugViewGroup(ViewAlignment::Right)
{
	fGroupList.push_back(&fDebugViewGroup);
}

void DebugInterface::update(UIInterface& f)
{
	InterfaceView::update(f);
	fDebugViewGroup.setPosition(sf::Vector2f(f.getFrame().getFrameWidth() - fDebugViewGroup.calculateWidth(), 0));
}