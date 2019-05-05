#include "MapEditorInterface.h"

MapEditorInterface::MapEditorInterface(UIInterface& f) : InterfaceView(f), fMapEditorControlsViewGroup(f)
{
	fGroupList.push_back(&fMapEditorControlsViewGroup);
}