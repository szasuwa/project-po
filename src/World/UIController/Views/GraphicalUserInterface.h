#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/ControlsViewGroup.h"
#include "../ViewGroups/InfoViewGroup.h"
#include "../ViewGroups/UserViewGroup.h"


class GraphicalUserInterface : public InterfaceView
{
	FrameInterface& fFrame;
	ControlsViewGroup fControlsViewGroup;
	InfoViewGroup fInfoViewGroup;
	UserViewGroup fUserViewGroup;

public:
	explicit GraphicalUserInterface(UIInterface& f);

	virtual void update();
};