#include "DebugInterface.h"

DebugInterface::DebugInterface() : fDebugViewGroup(ViewAlignment::Right)
{
	fGroupList.push_back(&fDebugViewGroup);
}

void DebugInterface::update(GameEngineInterface& f)
{
	InterfaceView::update(f);
	fDebugViewGroup.setPosition(sf::Vector2f(f.getFrameInterface().getFrameWidth() - fDebugViewGroup.calculateWidth(), 0));
}