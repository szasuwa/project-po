#pragma once
#include "../../Interfaces/UIInterface.h"
#include "../InterfaceType.h"

class MapSelectionViewAction : public ViewAction {
	unsigned int fUiType;
	UIInterface& fUi;
	int fIndex = -1;
	std::string fName = "";

public:
	explicit MapSelectionViewAction(UIInterface&f, const unsigned int& t, const int & i) : fUi(f), fUiType(t), fIndex(i) {};
	explicit MapSelectionViewAction(UIInterface&f, const unsigned int& t, const std::string& n) : fUi(f), fUiType(t), fName(n) {};
	virtual void operator() () { 
		bool load;
		if (fIndex >= 0) {
			if (!fUi.getMap().load(fIndex))
				return;
		}
		else if(fName.length() > 0)
		{
			if (!fUi.getMap().load(fName))
				return;
		}
		else 
		{
			return;
		}

		fUi.broadcastVisibilityChange(false);
		fUi.addUIView((unsigned int)InterfaceType::Gui);
	};
};