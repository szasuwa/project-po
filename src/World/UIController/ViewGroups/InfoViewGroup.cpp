#include "InfoViewGroup.h"

InfoViewGroup::InfoViewGroup(UIInterface& f) : InfoViewGroup(f, ViewAlignment::Left)
{
}

InfoViewGroup::InfoViewGroup(UIInterface& f, const ViewAlignment& a) : ViewGroup(f, a), fMapEditorKey(f), fDebugKey(f), fMapResetKey(f)
{
	fMapEditorKey.setText(Key::toString((InputKey)KeyBinding::MapEditor) + " - Map Editor");
	fDebugKey.setText(Key::toString((InputKey)KeyBinding::Debug) + " - Debug");
	fMapResetKey.setText(Key::toString((InputKey)KeyBinding::ResetMap) + " - Reset Map");

	fItemList.push_back(&fMapEditorKey);
	fItemList.push_back(&fDebugKey);
	fItemList.push_back(&fMapResetKey);
}