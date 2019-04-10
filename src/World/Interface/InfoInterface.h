#pragma once
#include "Bases/InterfaceGroup.h"
#include "Bases/InterfaceText.h"
#include "../Frame.h"


class InfoInterface : public InterfaceGroup {
	InterfaceText fDebugKey;
	InterfaceText fMapEditorKey;
public:
	InfoInterface();
	explicit InfoInterface(Alignment align);
	void update();
};