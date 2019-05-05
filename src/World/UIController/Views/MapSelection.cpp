#include "MapSelection.h"

MapSelection::MapSelection() : fMapSelectionViewGroup(ViewAlignment::Left)
{
	fGroupList.push_back(&fMapSelectionViewGroup);
}