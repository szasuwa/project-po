#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../InterfaceType.h"
#include "../ViewGroups/EndGameViewGroup.h"
#include "../ViewGroups/BackToMenuViewGroup.h"


class EndGameInterface : public InterfaceView
{
	EndGameViewGroup fEndGameViewGroup;
	BackToMenuViewGroup fBackToMenuViewGroup;

public:
	explicit EndGameInterface(GameEngineInterface& f);

	virtual void update(GameEngineInterface& f);

	virtual void setProperty(const unsigned int& i, const std::string& v);
};