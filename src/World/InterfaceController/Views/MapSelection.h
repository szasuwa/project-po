#pragma once
#include "../Interfaces/InterfaceView.h"
#include "../ViewGroups/MapSelectionViewGroup.h"


class MapSelection : public InterfaceView
{
	MapSelectionViewGroup fMapSelectionViewGroup;

public:
	MapSelection();
};