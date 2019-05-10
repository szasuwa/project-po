#pragma once
#include "ViewAction.h"
#include "../InterfaceType.h"
#include "../UIController.h"
#include "../../Interfaces/GameEngineInterface.h"
#include "../../Interfaces/UIInterface.h"


class InterfaceSelectionViewAction : public ViewAction {
	GameEngineInterface& fEngine;
	InterfaceType fInterfaceType;

public:
	explicit InterfaceSelectionViewAction(GameEngineInterface &e, const InterfaceType & s):fInterfaceType(s), fEngine(e) {};
	virtual void operator() () {
		UIInterface& ui = fEngine.getUIInterface();
		
		ui.broadcastVisibilityChange(false);
		ui.addUIView((unsigned int)fInterfaceType);
		ui.setViewVisibility((unsigned int)fInterfaceType, true);
	};
};