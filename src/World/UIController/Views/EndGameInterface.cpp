#include "EndGameInterface.h"

EndGameInterface::EndGameInterface(GameEngineInterface& f) : fEndGameViewGroup(ViewAlignment::Center), fBackToMenuViewGroup(f, ViewAlignment::Right)
{
	fPropertyList.resize(2);
	fPropertyList[0] = "0";
	fPropertyList[1] = "00:00";
	fGroupList.push_back(&fEndGameViewGroup);
	fGroupList.push_back(&fBackToMenuViewGroup);
}

void EndGameInterface::update(GameEngineInterface& f)
{
	InterfaceView::update(f);

	FrameInterface &frame = f.getFrameInterface();
	float width = frame.getFrameWidth();
	float height = frame.getFrameHeight();

	fEndGameViewGroup.setPosition(sf::Vector2f((width - fEndGameViewGroup.calculateWidth())/2, (height - fEndGameViewGroup.calculateHeight()) / 2));

	float offset = 20;
	fBackToMenuViewGroup.setPosition(sf::Vector2f(width - fBackToMenuViewGroup.calculateWidth() - offset, height - fBackToMenuViewGroup.calculateHeight() - offset));
}

void EndGameInterface::setProperty(const unsigned int& i, const std::string& v)
{
	InterfaceView::setProperty(i, v);

	fEndGameViewGroup.setPoints(fPropertyList[0]);
	fEndGameViewGroup.setTime(fPropertyList[1]);
}