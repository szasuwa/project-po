#pragma once
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../Frame/Frame.h"
#include "../../InputController/KeyController.h"


class MapEditorControlsViewGroup : public ViewGroup {
	static bool fVerticalLockStatus;
	static bool fHorizontalLockStatus;
	static bool fAxisLockUpdated;

	static bool fGridSnapStatus;
	static bool fGridSnapUpdated;
	static bool fTimeFlowStatus;
	static bool fTimeFlowUpdated;

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
	MapEditorControlsViewGroup();
	explicit MapEditorControlsViewGroup(const ViewAlignment& a);

	void update();

	static void reportAxisLockStatus(bool v, bool h);
	static void reportGridSnapStatus(bool s);
	static void reportTimeFlowStatus(bool s);
};