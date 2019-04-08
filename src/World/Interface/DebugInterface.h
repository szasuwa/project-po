#pragma once
#include "Base/InterfaceGroup.h"
#include "Base/InterfaceText.h"
#include "../Frame.h"
#include "../../GameConstants.h"


class DebugInterface : public InterfaceGroup {
	InterfaceText fFpsMeter;
	InterfaceText fVersion;
public:
	DebugInterface();
	explicit DebugInterface(Alignment align);
	void update();
};