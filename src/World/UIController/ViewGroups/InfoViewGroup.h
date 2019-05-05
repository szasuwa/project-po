#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../InputController/KeyBinding.h"


class InfoViewGroup : public ViewGroup {
	TextViewItem fDebugKey;
	TextViewItem fMapEditorKey;
	TextViewItem fMapResetKey;

public:
	explicit InfoViewGroup(const ViewAlignment& a);
};