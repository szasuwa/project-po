#pragma once
#include <exception>

#include "../../Interfaces/GameEngineInterface.h"
#include "../../Interfaces/MapInterface.h"
#include "../../Interfaces/UIInterface.h"
#include "../InterfaceType.h"


class MapSelectionViewAction : public ViewAction {
	unsigned int fUiType;
	GameEngineInterface& fEngine;
	int fIndex = -1;
	std::string fName = "";

public:
	explicit MapSelectionViewAction(GameEngineInterface&f, const unsigned int& t, const int & i) : fEngine(f), fUiType(t), fIndex(i) {};
	explicit MapSelectionViewAction(GameEngineInterface&f, const unsigned int& t, const std::string& n) : fEngine(f), fUiType(t), fName(n) {};
	virtual void operator() () { 
		UIInterface& ui = fEngine.getUIInterface();
		ui.addUIView((unsigned int)InterfaceType::Gui);

		if (fIndex >= 0) {
			if (!fEngine.getMapInterface().load(fIndex))
				return;
		}
		else if(fName.length() > 0)
		{
			if (!fEngine.getMapInterface().load(fName))
				return;
		}
		else 
		{
			throw std::invalid_argument("Map name not provided");
		}

		ui.broadcastVisibilityChange(false);
		ui.setViewVisibility((unsigned int)InterfaceType::Gui, true);
	};
};