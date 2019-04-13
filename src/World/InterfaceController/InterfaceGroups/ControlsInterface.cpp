#include "ControlsInterface.h"


ControlsInterface::ControlsInterface(const Alignment & a) : InterfaceGroup(a)
{
	fMoveLeftKey.setText("Move Left " + KeyController::getInstance().getKeyGroup(KeyBinding::MoveLeft).toString());
	fMoveRightKey.setText("Move Right " + KeyController::getInstance().getKeyGroup(KeyBinding::MoveRight).toString());
	fMoveJumpKey.setText("Jump " + KeyController::getInstance().getKeyGroup(KeyBinding::Jump).toString());

	fItemList.push_back(&fMoveLeftKey);
	fItemList.push_back(&fMoveRightKey);
	fItemList.push_back(&fMoveJumpKey);
}

void ControlsInterface::update()
{
}