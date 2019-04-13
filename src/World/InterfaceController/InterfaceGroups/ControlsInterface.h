#pragma once
#include "InterfaceGroup.h"
#include "../InterfaceItems/InterfaceText.h"
#include "../../Frame/Frame.h"
#include "../../KeyboardController/KeyController.h"


class ControlsInterface : public InterfaceGroup {
	InterfaceText fMoveLeftKey;
	InterfaceText fMoveRightKey;
	InterfaceText fMoveJumpKey;

public:
	explicit ControlsInterface(const Alignment & a);
	void update();
};