#pragma once
#include "InterfaceGroup.h"
#include "../InterfaceItems/InterfaceText.h"
#include "../../Frame/Frame.h"
#include "../../KeyboardController/KeyController.h"


class MapEditorInterface : public InterfaceGroup {
	static bool fVerticalLockStatus;
	static bool fHorizontalLockStatus;
	static bool fAxisLockUpdated;

	static bool fGridSnapStatus;
	static bool fGridSnapUpdated;

	InterfaceText fSelectionKey;
	InterfaceText fResetKey;
	InterfaceText fSaveKey;

	InterfaceText fDeleteKey;
	InterfaceText fCloneKey;
	InterfaceText fMoveKey;
	InterfaceText fResizeKey;

	InterfaceText fVerticalLockKey;
	InterfaceText fHorizontalLockKey;
	InterfaceText fGridSnapKey;

	InterfaceText fGhostPlayerKey;
	InterfaceText fGhostPlatformKey;
	InterfaceText fGhostPointKey;

public:
	MapEditorInterface();
	explicit MapEditorInterface(const Alignment & a);
	void update();

	static void reportAxisLockStatus(bool v, bool h);
	static void reportGridSnapStatus(bool s);
};