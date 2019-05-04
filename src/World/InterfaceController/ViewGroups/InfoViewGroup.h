#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../Frame/Frame.h"
#include "../../InputController/KeyController.h"


class InfoViewGroup : public ViewGroup {
	TextViewItem fDebugKey;
	TextViewItem fMapEditorKey;
	TextViewItem fMapResetKey;

public:
	InfoViewGroup();
	explicit InfoViewGroup(const ViewAlignment& a);
};