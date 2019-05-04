#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/MainMenuViewGroup.h"


class MainMenu : public InterfaceView 
{
	MainMenuViewGroup fMainMenuViewGroup;

public:
	MainMenu();
};