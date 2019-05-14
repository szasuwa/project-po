#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/MainMenuViewGroup.h"
#include "../ViewGroups/VersionViewGroup.h"


class MainMenu : public InterfaceView 
{
	MainMenuViewGroup fMainMenuViewGroup;
	VersionViewGroup fVersionViewGroup;

public:
	explicit MainMenu(GameEngineInterface& f);

	virtual void update(GameEngineInterface& f);
};