#pragma once
#include "Base/InterfaceGroup.h"
#include "Base/InterfaceText.h"
#include "../Frame.h"


class InfoInterface : public InterfaceGroup {
	InterfaceText fDebugKey;
	InterfaceText fMapEditorKey;
public:
	InfoInterface();
	explicit InfoInterface(Alignment align);
	void update();
};