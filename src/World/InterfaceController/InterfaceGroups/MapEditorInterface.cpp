#include "MapEditorInterface.h"
bool MapEditorInterface::fVerticalLockStatus = false;
bool MapEditorInterface::fHorizontalLockStatus = false;
bool MapEditorInterface::fAxisLockUpdated = true;
bool MapEditorInterface::fGridSnapStatus = false;
bool MapEditorInterface::fGridSnapUpdated = true;



MapEditorInterface::MapEditorInterface() : InterfaceGroup() 
{
}

MapEditorInterface::MapEditorInterface(const Alignment & a) : InterfaceGroup(a)
{
	
	fSelectionKey.setText("[LPM] Select Item / Place Ghost");
	fResetKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorReset).toString() + " Reset Map");
	fSaveKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorSave).toString() + " Save Map");

	fDeleteKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorDelete).toString() + " Delete Item / Ghost");
	fCloneKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorClone).toString() + " Clone");
	fMoveKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorMove).toString() + "Move");
	fResizeKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorResize).toString() + " Resize");

	fGridSnapKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorGridLock).toString() + " Snap To Grid");
	fVerticalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorVLock).toString() + " Vertical Lock");
	fHorizontalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorHLock).toString() + " Horizontal Lock");

	fGhostPlayerKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorGhostPlayer).toString() + " Player Ghost");
	fGhostPlatformKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorGhostPlatform).toString() + " Platform Ghost");
	fGhostPointKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorGhostPoint).toString() + " Point Ghost");


	fItemList.push_back(&fSelectionKey);
	fItemList.push_back(&fResetKey);
	fItemList.push_back(&fSaveKey);

	fItemList.push_back(&fDeleteKey);
	fItemList.push_back(&fCloneKey);
	fItemList.push_back(&fMoveKey);
	fItemList.push_back(&fResizeKey);

	fItemList.push_back(&fGridSnapKey);
	fItemList.push_back(&fVerticalLockKey);
	fItemList.push_back(&fHorizontalLockKey);

	fItemList.push_back(&fGhostPlayerKey);
	fItemList.push_back(&fGhostPlatformKey);
	fItemList.push_back(&fGhostPointKey);
}

void MapEditorInterface::update()
{
	if (fAxisLockUpdated) 
	{
		fAxisLockUpdated = false;
		fVerticalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorVLock).toString() + " Vertical Lock" + (fVerticalLockStatus ? " : On" : " : Off"));
		fHorizontalLockKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorHLock).toString() + " Horizontal Lock" + (fHorizontalLockStatus ? " : On" : " : Off"));
	}

	if (fGridSnapUpdated)
	{
		fGridSnapUpdated = false;
		fGridSnapKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditorGridLock).toString() + " Snap To Grid" + (fGridSnapStatus ? " : On" : " : Off"));
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