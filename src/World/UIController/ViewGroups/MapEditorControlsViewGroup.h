#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../InputController/KeyBinding.h"


class MapEditorControlsViewGroup : public ViewGroup {
	std::string  fVerticalLockStatus = "Off";
	std::string  fHorizontalLockStatus = "Off";

	std::string fGridSnapStatus = "On";

	std::string fTimeFlowStatus = "Off";
	bool fTimeFlowUpdated = true;

	SeparatorViewItem fSeparator;

	TextViewItem fTimeKey;
	TextViewItem fResetKey;
	TextViewItem fSaveKey;
	TextViewItem fExitKey;
	TextViewItem fCancelKey;

	TextViewItem fSelectionKey;

	TextViewItem fDeleteKey;
	TextViewItem fCloneKey;
	TextViewItem fMoveKey;
	TextViewItem fResizeKey;
	TextViewItem fLinkKey;

	TextViewItem fVerticalLockKey;
	TextViewItem fHorizontalLockKey;
	TextViewItem fGridSnapKey;

	TextViewItem fGhostPlayerKey;
	TextViewItem fGhostPlatformKey;
	TextViewItem fGhostPointKey;
	TextViewItem fGhostPortalKey;
	TextViewItem fGhostBoxKey;

public:
	explicit MapEditorControlsViewGroup(const ViewAlignment& a);

	void update(GameEngineInterface& f);

	void setVerticalLock(const std::string& s);
	void setHorizontalLock(const std::string& s);
	void setGridSnap(const std::string& s);
	void setTimeFlow(const std::string& s);
};