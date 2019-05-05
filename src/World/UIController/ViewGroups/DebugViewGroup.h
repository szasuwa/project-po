#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../../GameConstants.h"


class DebugViewGroup : public ViewGroup {
	FrameInterface& fFrame;

	TextViewItem fFpsMeter;
	TextViewItem fVersion;
	SeparatorViewItem fSeparator;

public:
	explicit DebugViewGroup(UIInterface& f);
	DebugViewGroup(UIInterface& f, const ViewAlignment& a);

	void update();
};