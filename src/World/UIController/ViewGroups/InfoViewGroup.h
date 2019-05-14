#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../InputController/KeyBinding.h"
#include "../../InputController/Keys/Key.h"


class InfoViewGroup : public ViewGroup {
	TextViewItem fDebugKey;
	TextViewItem fMapEditorKey;
	TextViewItem fMapResetKey;

public:
	explicit InfoViewGroup(const ViewAlignment& a);
};