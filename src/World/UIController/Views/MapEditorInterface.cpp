#include "MapEditorInterface.h"

MapEditorInterface::MapEditorInterface() : fMapEditorControlsViewGroup(ViewAlignment::Left)
{
	fGroupList.push_back(&fMapEditorControlsViewGroup);
}