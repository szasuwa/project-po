#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../../Frame/Frame.h"
#include "../../KeyboardController/KeyController.h"


class ControlsViewGroup : public ViewGroup {
	TextViewItem fMoveLeftKey;
	TextViewItem fMoveRightKey;
	TextViewItem fMoveJumpKey;

public:
	ControlsViewGroup();
	explicit ControlsViewGroup(const ViewAlignment& a);

	void update();
};