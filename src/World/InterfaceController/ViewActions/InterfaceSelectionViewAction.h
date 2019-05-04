#pragma once
#include "../InterfaceController.h"


class InterfaceSelectionViewAction : public ViewAction {
	InterfaceType fInterfaceType;

public:
	explicit InterfaceSelectionViewAction(const InterfaceType & s):fInterfaceType(s) {};
	virtual void operator() () { InterfaceController::getInstance().selectInterface(fInterfaceType); };
};