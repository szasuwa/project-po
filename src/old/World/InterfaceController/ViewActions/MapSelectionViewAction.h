#pragma once
#include "../InterfaceController.h"
#include "../../MapController/MapController.h"

class MapSelectionViewAction : public ViewAction {
	int fIndex = -1;
	std::string fName = "";

public:
	explicit MapSelectionViewAction(const int & i):fIndex(i) {};
	explicit MapSelectionViewAction(const std::string& n) :fName(n) {};
	virtual void operator() () { 
		bool load;
		if (fIndex >= 0) {
			if (!MapController::getInstance().load(fIndex))
				return;
		}
		else if(fName.length() > 0)
		{
			if (!MapController::getInstance().load(fName))
				return;
		}
		else 
		{
			return;
		}

		InterfaceController::getInstance().selectInterface(InterfaceType::Gui);
	};
};