#include "MapEditorInterface.h"
bool MapEditorInterface::fVerticalLockStatus = false;
bool MapEditorInterface::fHorizontalLockStatus = false;
bool MapEditorInterface::fAxisLockUpdated = true;
bool MapEditorInterface::fGridSnapStatus = false;
bool MapEditorInterface::fGridSnapUpdated = true;



MapEditorInterface::MapEditorInterface() : MapEditorInterface(Alignment::Left) {
}

MapEditorInterface::MapEditorInterface(Alignment align) {
	
	fAlignment = align;
	fSelectionKey.setText(std::string("LPM - Select Item / Place Ghost"));
	fMoveKey.setText(std::string("Left Ctrl - Move"));
	fResizeKey.setText(std::string("Left Shift - Resize"));
	fVerticalLockKey.setText(std::string("Q - Vertical Lock"));
	fHorizontalLockKey.setText(std::string("E - Horizontal Lock"));
	fGridSnapKey.setText(std::string("TAB - Snap To Grid"));
	fDeleteKey.setText(std::string("Delete - Delete Item / Ghost"));
	fGhostPlayerKey.setText(std::string("1 - Player Ghost"));
	fGhostPlatformKey.setText(std::string("2 - Platform Ghost"));
	fGhostPointKey.setText(std::string("3 - Point Ghost"));

	fItemList.push_back(&fSelectionKey);
	fItemList.push_back(&fDeleteKey);
	fItemList.push_back(&fGridSnapKey);
	fItemList.push_back(&fMoveKey);
	fItemList.push_back(&fResizeKey);
	fItemList.push_back(&fVerticalLockKey);
	fItemList.push_back(&fHorizontalLockKey);
	fItemList.push_back(&fGhostPlayerKey);
	fItemList.push_back(&fGhostPlatformKey);
	fItemList.push_back(&fGhostPointKey);
}

void MapEditorInterface::update() {
	if (fAxisLockUpdated) {
		fAxisLockUpdated = false;
		fVerticalLockKey.setText(std::string("Q - Vertical Lock") + (fVerticalLockStatus ? " : On" : " : Off"));
		fHorizontalLockKey.setText(std::string("E - Horizontal Lock") + (fHorizontalLockStatus ? " : On" : " : Off"));
	}

	if (fGridSnapUpdated) {
		fGridSnapUpdated = false;
		fGridSnapKey.setText(std::string("TAB - Snap To Grid") + (fGridSnapStatus ? " : On" : " : Off"));
	}
	
}

void MapEditorInterface::reportAxisLockStatus(bool v, bool h) {
	fVerticalLockStatus = v;
	fHorizontalLockStatus = h;
	fAxisLockUpdated = true;
}

void MapEditorInterface::reportGridSnapStatus(bool s) {
	fGridSnapStatus = s;
	fGridSnapUpdated = true;
}