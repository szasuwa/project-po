#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/MapEditorControlsViewGroup.h"
#include "../ViewProperties.h"


class MapEditorInterface : public InterfaceView
{
	MapEditorControlsViewGroup fMapEditorControlsViewGroup;

public:
	MapEditorInterface();

	virtual void setProperty(const unsigned int& i, const std::string& v);
};