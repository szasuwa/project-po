#pragma once
#include "../Interfaces/OverlayView.h"
#include "../ViewGroups/DebugViewGroup.h"


class DebugOverlay : public OverlayView
{
	DebugViewGroup fDebugViewGroup;

public:
	DebugOverlay();

	virtual void update();
};