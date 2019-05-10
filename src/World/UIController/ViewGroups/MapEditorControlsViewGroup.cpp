#include "MapEditorControlsViewGroup.h"

MapEditorControlsViewGroup::MapEditorControlsViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fSelectionKey.setText("[" + Key::toString((InputKey)KeyBinding::LeftClick) + "] Select Item / Place Ghost");

	fTimeKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorTime) + "] Time Flow");
	fResetKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorReset) + "] Reset Map");
	fSaveKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorSave) + "] Save Map");
	fExitKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorExit) + "] Quit Editor (Save)");
	fCancelKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorCancel) + "] Quit Editor (Cancel)");

	fDeleteKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorDelete) + "] Delete Item / Ghost");
	fMoveKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorMove) + "] Move");
	fResizeKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorResize) + "] Resize");
	fCloneKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorClone) + "] Clone");
	fLinkKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorLinkPortal) + "] Edit Portal Link");

	fGridSnapKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorGridLock) + "] Snap To Grid");
	fVerticalLockKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorVLock) + "] Vertical Lock");
	fHorizontalLockKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorHLock) + "] Horizontal Lock");

	fGhostPlayerKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorGhostPlayer) + "] Player Ghost");
	fGhostPlatformKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorGhostPlatform) + "] Platform Ghost");
	fGhostPointKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorGhostPoint) + "] Point Ghost");
	fGhostPortalKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorGhostPortal) + "] Portal Ghost");
	fGhostBoxKey.setText("[" + Key::toString((InputKey)KeyBinding::MapEditorGhostBox) + "] Box Ghost");


	fItemList.push_back(&fSelectionKey);
	fItemList.push_back(&fSeparator);

	fItemList.push_back(&fTimeKey);
	fItemList.push_back(&fResetKey);
	fItemList.push_back(&fSaveKey);
	fItemList.push_back(&fExitKey);
	fItemList.push_back(&fCancelKey);
	fItemList.push_back(&fSeparator);

	fItemList.push_back(&fDeleteKey);
	fItemList.push_back(&fMoveKey);
	fItemList.push_back(&fResizeKey);
	fItemList.push_back(&fCloneKey);
	fItemList.push_back(&fLinkKey);
	fItemList.push_back(&fSeparator);

	fItemList.push_back(&fGridSnapKey);
	fItemList.push_back(&fVerticalLockKey);
	fItemList.push_back(&fHorizontalLockKey);
	fItemList.push_back(&fSeparator);

	fItemList.push_back(&fGhostPlayerKey);
	fItemList.push_back(&fGhostPlatformKey);
	fItemList.push_back(&fGhostPointKey);
	fItemList.push_back(&fGhostPortalKey);
	fItemList.push_back(&fGhostBoxKey);
}

void MapEditorControlsViewGroup::update(GameEngineInterface& f)
{
}

void MapEditorControlsViewGroup::setVerticalLock(const std::string& s)
{
	fVerticalLockKey.setText(Key::toString((InputKey)KeyBinding::MapEditorVLock) + " - Vertical Lock: " + s);
}

void MapEditorControlsViewGroup::setHorizontalLock(const std::string& s)
{
	fHorizontalLockKey.setText(Key::toString((InputKey)KeyBinding::MapEditorHLock) + " - Horizontal Lock: " + s);
}

void MapEditorControlsViewGroup::setGridSnap(const std::string& s)
{
	fGridSnapKey.setText(Key::toString((InputKey)KeyBinding::MapEditorGridLock) + " - Snap To Grid: " + s);
}

void MapEditorControlsViewGroup::setTimeFlow(const std::string& s)
{
	fTimeKey.setText(Key::toString((InputKey)KeyBinding::MapEditorTime) + " - Time Flow: " + s);
}