#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../InputController/KeyBinding.h"


class MapEditorControlsViewGroup : public ViewGroup {
	bool fVerticalLockStatus = false;
	bool fHorizontalLockStatus = false;
	bool fAxisLockUpdated = true;

	bool fGridSnapStatus = true;
	bool fGridSnapUpdated = true;
	bool fTimeFlowStatus = false;
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
	explicit MapEditorControlsViewGroup(UIInterface& f);
	MapEditorControlsViewGroup(UIInterface& f, const ViewAlignment& a);

	void update();

	void reportAxisLockStatus(bool v, bool h);
	void reportGridSnapStatus(bool s);
	void reportTimeFlowStatus(bool s);
};