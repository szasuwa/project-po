#include "ControlsViewGroup.h"


ControlsViewGroup::ControlsViewGroup() : ControlsViewGroup(ViewAlignment::Left)
{
}

ControlsViewGroup::ControlsViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fMoveLeftKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MoveLeft).toString() + " Move Left");
	fMoveRightKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MoveRight).toString() + " Move Right");
	fMoveJumpKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::Jump).toString() + " Jump");

	fItemList.push_back(&fMoveLeftKey);
	fItemList.push_back(&fMoveRightKey);
	fItemList.push_back(&fMoveJumpKey);
}

void ControlsViewGroup::update()
{
}