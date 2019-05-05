#include "InfoViewGroup.h"

InfoViewGroup::InfoViewGroup() : InfoViewGroup(ViewAlignment::Left)
{
}

InfoViewGroup::InfoViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fMapEditorKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditor).toString() + " Map Editor");
	fDebugKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::Debug).toString() + " Debug");
	fMapResetKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::ResetMap).toString() + " Reset Map");

	fItemList.push_back(&fMapEditorKey);
	fItemList.push_back(&fDebugKey);
	fItemList.push_back(&fMapResetKey);
}