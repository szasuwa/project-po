#include "MapEditorInterface.h"
bool MapEditorInterface::fVerticalLockStatus = false;
bool MapEditorInterface::fHorizontalLockStatus = false;
bool MapEditorInterface::fAxisLockUpdated = true;
bool MapEditorInterface::fGridSnapStatus = false;
bool MapEditorInterface::fGridSnapUpdated = true;
bool MapEditorInterface::fTimeFlowStatus = false;
bool MapEditorInterface::fTimeFlowUpdated = true;


MapEditorInterface::MapEditorInterface(const Alignment & a) : InterfaceGroup(a)
{
	fSelectionKey.setText("[LPM] Select Item / Place Ghost");

	fTimeKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorTime).toString() + " Time Flow");
	fResetKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorReset).toString() + " Reset Map");
	fSaveKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorSave).toString() + " Save Map");
	fExitKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorExit).toString() + " Quit Editor (Save)");
	fCancelKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorCancel).toString() + " Quit Editor (Cancel)");

	fDeleteKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorDelete).toString() + " Delete Item / Ghost / Link");
	fCloneKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorClone).toString() + " Clone");
	fMoveKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorMove).toString() + "Move");
	fResizeKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorResize).toString() + " Resize");
	fLinkKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorLinkPortal).toString() + " Edit Portal Link");

	fGridSnapKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGridLock).toString() + " Snap To Grid");
	fVerticalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorVLock).toString() + " Vertical Lock");
	fHorizontalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorHLock).toString() + " Horizontal Lock");

	fGhostPlayerKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGhostPlayer).toString() + " Player Ghost");
	fGhostPlatformKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGhostPlatform).toString() + " Platform Ghost");
	fGhostPointKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGhostPoint).toString() + " Point Ghost");
	fGhostPortalKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGhostPortal).toString() + " Portal Ghost");
	fGhostBoxKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGhostBox).toString() + " Box Ghost");
	


	fItemList.push_back(&fSelectionKey);
	fItemList.push_back(&fSeparator);
	

	fItemList.push_back(&fTimeKey);
	fItemList.push_back(&fResetKey);
	fItemList.push_back(&fSaveKey);
	fItemList.push_back(&fExitKey);
	fItemList.push_back(&fCancelKey);
	fItemList.push_back(&fSeparator);

	fItemList.push_back(&fDeleteKey);
	fItemList.push_back(&fCloneKey);
	fItemList.push_back(&fMoveKey);
	fItemList.push_back(&fResizeKey);
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

void MapEditorInterface::update()
{
	if (fAxisLockUpdated) 
	{
		fAxisLockUpdated = false;
		fVerticalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorVLock).toString() + " Vertical Lock" + (fVerticalLockStatus ? " : On" : " : Off"));
		fHorizontalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorHLock).toString() + " Horizontal Lock" + (fHorizontalLockStatus ? " : On" : " : Off"));
	}

	if (fGridSnapUpdated)
	{
		fGridSnapUpdated = false;
		fGridSnapKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorGridLock).toString() + " Snap To Grid" + (fGridSnapStatus ? " : On" : " : Off"));
	}

	if (fTimeFlowUpdated)
	{
		fTimeFlowUpdated = false;
		fTimeKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditorTime).toString() + " Time Flow" + (fTimeFlowStatus ? " : On" : " : Off"));
	}
	
}

void MapEditorInterface::reportAxisLockStatus(bool v, bool h)
{
	fVerticalLockStatus = v;
	fHorizontalLockStatus = h;
	fAxisLockUpdated = true;
}

void MapEditorInterface::reportGridSnapStatus(bool s)
{
	fGridSnapStatus = s;
	fGridSnapUpdated = true;
}

void MapEditorInterface::reportTimeFlowStatus(bool s)
{
	fTimeFlowStatus = s;
	fTimeFlowUpdated = true;
}