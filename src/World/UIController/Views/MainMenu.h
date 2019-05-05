#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/MainMenuViewGroup.h"


class MainMenu : public InterfaceView 
{
	FrameInterface& fFrame;
	MainMenuViewGroup fMainMenuViewGroup;

public:
	explicit MainMenu(UIInterface& f);

	virtual void update();
};