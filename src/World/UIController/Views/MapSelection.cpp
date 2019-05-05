#include "MapSelection.h"

MapSelection::MapSelection(UIInterface& f) : InterfaceView(f), fMapSelectionViewGroup(f)
{
	fGroupList.push_back(&fMapSelectionViewGroup);
}