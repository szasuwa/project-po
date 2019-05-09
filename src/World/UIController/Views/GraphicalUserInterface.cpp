#include "GraphicalUserInterface.h"

GraphicalUserInterface::GraphicalUserInterface() : fControlsViewGroup(ViewAlignment::Left), fInfoViewGroup(ViewAlignment::Left), fUserViewGroup(ViewAlignment::Left)
{
	fPropertyList.resize(1);
	fPropertyList[0] = "0";
	fGroupList.push_back(&fControlsViewGroup);
	fGroupList.push_back(&fInfoViewGroup);
	fGroupList.push_back(&fUserViewGroup);
}

void GraphicalUserInterface::update(GameEngineInterface& f)
{
	InterfaceView::update(f);

	fInfoViewGroup.setPosition(sf::Vector2f(0, 0));

	fUserViewGroup.setPosition(sf::Vector2f((f.getFrameInterface().getFrameWidth() - fUserViewGroup.calculateWidth())/2, 0));

	fControlsViewGroup.setPosition(fInfoViewGroup.getPosition() + sf::Vector2f(0, fInfoViewGroup.calculateHeight()));
}

void GraphicalUserInterface::setProperty(const unsigned int& i, const std::string& v)
{
	InterfaceView::setProperty(i, v);

	fUserViewGroup.setPoints(fPropertyList[0]);
}