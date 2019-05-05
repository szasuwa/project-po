#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/DebugViewGroup.h"


class DebugInterface : public InterfaceView
{
	DebugViewGroup fDebugViewGroup;

public:
	DebugInterface();

	virtual void update(UIInterface& f);
};