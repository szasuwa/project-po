#include "ControlsViewGroup.h"


ControlsViewGroup::ControlsViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fMoveLeftKey.setText("[" + Key::toString((InputKey)KeyBinding::MoveLeft) + "] Move Left");
	fMoveRightKey.setText("[" + Key::toString((InputKey)KeyBinding::MoveRight) + "] Move Right");
	fMoveJumpKey.setText("[" + Key::toString((InputKey)KeyBinding::Jump) + "] Jump");

	fItemList.push_back(&fMoveLeftKey);
	fItemList.push_back(&fMoveRightKey);
	fItemList.push_back(&fMoveJumpKey);
}