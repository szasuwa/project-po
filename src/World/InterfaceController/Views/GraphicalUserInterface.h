#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/ControlsViewGroup.h"
#include "../ViewGroups/InfoViewGroup.h"
#include "../ViewGroups/UserViewGroup.h"


class GraphicalUserInterface : public InterfaceView
{
	ControlsViewGroup fControlsViewGroup;
	InfoViewGroup fInfoViewGroup;
	UserViewGroup fUserViewGroup;

public:
	GraphicalUserInterface();

	virtual void update();
};