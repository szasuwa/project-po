#include "DebugOverlay.h"

DebugOverlay::DebugOverlay() : fDebugViewGroup(ViewAlignment::Right)
{
	fGroupList.push_back(&fDebugViewGroup);
}

void DebugOverlay::update()
{
	InterfaceView::update();

	Frame& frame = Frame::getInstance();

	fDebugViewGroup.setPosition(sf::Vector2f(frame.getFrameWidth() - fDebugViewGroup.calculateWidth(), 0));
}