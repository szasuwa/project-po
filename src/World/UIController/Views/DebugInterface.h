#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/DebugViewGroup.h"


class DebugInterface : public InterfaceView
{
	FrameInterface& fFrame;
	DebugViewGroup fDebugViewGroup;

public:
	explicit DebugInterface(UIInterface& f);

	virtual void update();
};