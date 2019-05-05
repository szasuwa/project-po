#include "InfoViewGroup.h"


InfoViewGroup::InfoViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fMapEditorKey.setText(Key::toString((InputKey)KeyBinding::MapEditor) + " - Map Editor");
	fDebugKey.setText(Key::toString((InputKey)KeyBinding::Debug) + " - Debug");
	fMapResetKey.setText(Key::toString((InputKey)KeyBinding::ResetMap) + " - Reset Map");

	fItemList.push_back(&fMapEditorKey);
	fItemList.push_back(&fDebugKey);
	fItemList.push_back(&fMapResetKey);
}