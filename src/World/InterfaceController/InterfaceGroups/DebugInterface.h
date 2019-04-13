#pragma once
#include "InterfaceGroup.h"
#include "../InterfaceItems/InterfaceText.h"
#include "../InterfaceItems/InterfaceSeparator.h"
#include "../../Frame/Frame.h"
#include "../../../GameConstants.h"


class DebugInterface : public InterfaceGroup {
	InterfaceText fFpsMeter;
	InterfaceText fVersion;
	InterfaceSeparator fSeparator;

public:
	explicit DebugInterface(const Alignment & a = Alignment::Left);
	void update();
};