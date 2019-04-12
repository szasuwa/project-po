#pragma once
#include "InterfaceGroup.h"
#include "../InterfaceItems/InterfaceText.h"
#include "../../Frame/Frame.h"
#include "../../KeyboardController/KeyController.h"


class InfoInterface : public InterfaceGroup {
	InterfaceText fDebugKey;
	InterfaceText fMapEditorKey;

public:
	explicit InfoInterface();
	explicit InfoInterface(const Alignment & a);
	void update();
};