#include "ControlsViewGroup.h"


ControlsViewGroup::ControlsViewGroup(UIInterface& f) : ControlsViewGroup(f, ViewAlignment::Left)
{
}

ControlsViewGroup::ControlsViewGroup(UIInterface& f, const ViewAlignment& a) : ViewGroup(f, a), fMoveLeftKey(f), fMoveRightKey(f), fMoveJumpKey(f)
{
	fMoveLeftKey.setText(Key::toString((InputKey)KeyBinding::MoveLeft) + " - Move Left");
	fMoveRightKey.setText(Key::toString((InputKey)KeyBinding::MoveRight) + " - Move Right");
	fMoveJumpKey.setText(Key::toString((InputKey)KeyBinding::Jump) + "- Jump");

	fItemList.push_back(&fMoveLeftKey);
	fItemList.push_back(&fMoveRightKey);
	fItemList.push_back(&fMoveJumpKey);
}