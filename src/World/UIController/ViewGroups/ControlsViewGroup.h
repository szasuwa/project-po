#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../../Frame/Frame.h"
#include "../../InputController/KeyBinding.h"


class ControlsViewGroup : public ViewGroup {
	TextViewItem fMoveLeftKey;
	TextViewItem fMoveRightKey;
	TextViewItem fMoveJumpKey;

public:
	explicit ControlsViewGroup(const ViewAlignment& a);
};