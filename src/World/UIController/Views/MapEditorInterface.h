#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/MapEditorControlsViewGroup.h"


class MapEditorInterface : public InterfaceView
{
	MapEditorControlsViewGroup fMapEditorControlsViewGroup;

public:
	MapEditorInterface();
};