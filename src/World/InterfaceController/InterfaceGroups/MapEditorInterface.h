#pragma once
#include "InterfaceGroup.h"
#include "../InterfaceItems/InterfaceText.h"
#include "../InterfaceItems/InterfaceSeparator.h"
#include "../../Frame/Frame.h"
#include "../../KeyboardController/KeyController.h"


class MapEditorInterface : public InterfaceGroup {
	static bool fVerticalLockStatus;
	static bool fHorizontalLockStatus;
	static bool fAxisLockUpdated;

	static bool fGridSnapStatus;
	static bool fGridSnapUpdated;
	static bool fTimeFlowStatus;
	static bool fTimeFlowUpdated;

	InterfaceSeparator fSeparator;

	InterfaceText fTimeKey;
	InterfaceText fResetKey;
	InterfaceText fSaveKey;
	InterfaceText fExitKey;
	InterfaceText fCancelKey;

	InterfaceText fSelectionKey;

	InterfaceText fDeleteKey;
	InterfaceText fCloneKey;
	InterfaceText fMoveKey;
	InterfaceText fResizeKey;
	InterfaceText fLinkKey;

	InterfaceText fVerticalLockKey;
	InterfaceText fHorizontalLockKey;
	InterfaceText fGridSnapKey;

	InterfaceText fGhostPlayerKey;
	InterfaceText fGhostPlatformKey;
	InterfaceText fGhostPointKey;
	InterfaceText fGhostPortalKey;
	InterfaceText fGhostBoxKey;

public:
	explicit MapEditorInterface(const Alignment & a);
	void update();

	static void reportAxisLockStatus(bool v, bool h);
	static void reportGridSnapStatus(bool s);
	static void reportTimeFlowStatus(bool s);
};