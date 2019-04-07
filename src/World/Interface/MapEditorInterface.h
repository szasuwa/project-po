#pragma once
#include "Base/InterfaceGroup.h"
#include "Base/InterfaceText.h"
#include "../Frame.h"


class MapEditorInterface : public InterfaceGroup {
	static bool fVerticalLockStatus;
	static bool fHorizontalLockStatus;
	static bool fAxisLockUpdated;

	InterfaceText fSelectionKey;
	InterfaceText fMoveKey;
	InterfaceText fResizeKey;
	InterfaceText fVerticalLockKey;
	InterfaceText fHorizontalLockKey;
	InterfaceText fDeleteKey;
	InterfaceText fGhostPlayerKey;
	InterfaceText fGhostPlatformKey;
	InterfaceText fGhostPointKey;
public:
	MapEditorInterface();
	explicit MapEditorInterface(Alignment align);
	void update();

	static void reportAxisLockStatus(bool v, bool h);
};