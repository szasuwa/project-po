#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/ControlsViewGroup.h"
#include "../ViewGroups/InfoViewGroup.h"
#include "../ViewGroups/UserViewGroup.h"


class GraphicalUserInterface : public InterfaceView
{
	ControlsViewGroup fControlsViewGroup;
	InfoViewGroup fInfoViewGroup;
	UserViewGroup fUserViewGroup;

public:
	explicit GraphicalUserInterface();

	virtual void update(GameEngineInterface& f);

	virtual void setProperty(const unsigned int& i, const std::string& v);
};