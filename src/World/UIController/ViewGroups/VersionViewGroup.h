#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../../../GameConstants.h"


class VersionViewGroup : public ViewGroup {
	TextViewItem fVersion;
	TextViewItem fCopyright;

public:
	explicit VersionViewGroup(const ViewAlignment& a);
};