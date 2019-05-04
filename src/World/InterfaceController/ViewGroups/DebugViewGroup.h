#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../Frame/Frame.h"
#include "../../../GameConstants.h"


class DebugViewGroup : public ViewGroup {
	TextViewItem fFpsMeter;
	TextViewItem fVersion;
	SeparatorViewItem fSeparator;

public:
	DebugViewGroup();
	explicit DebugViewGroup(const ViewAlignment& a);

	void update();
};