#pragma once
#include "Base/InterfaceGroup.h"
#include "Base/InterfaceText.h"
#include "../Frame.h"


class DebugInterface : public InterfaceGroup {
	InterfaceText fFpsMeter;
public:
	DebugInterface();
	explicit DebugInterface(Alignment align);
	void update();
};