#include "MapEditorInterface.h"

MapEditorInterface::MapEditorInterface() : fMapEditorControlsViewGroup(ViewAlignment::Left)
{
	fPropertyList.resize(4);
	fPropertyList[0] = "Off";
	fPropertyList[1] = "Off";
	fPropertyList[2] = "On";
	fPropertyList[3] = "Off";

	fMapEditorControlsViewGroup.setVerticalLock(fPropertyList[0]);
	fMapEditorControlsViewGroup.setHorizontalLock(fPropertyList[1]);
	fMapEditorControlsViewGroup.setGridSnap(fPropertyList[2]);
	fMapEditorControlsViewGroup.setTimeFlow(fPropertyList[3]);

	fGroupList.push_back(&fMapEditorControlsViewGroup);
}

void MapEditorInterface::setProperty(const unsigned int& i, const std::string& v)
{
	InterfaceView::setProperty(i, v);
	switch (i)
	{
		case MapEditorPropertyMap::VerticalLock:
			fMapEditorControlsViewGroup.setVerticalLock(v);
			break;

		case MapEditorPropertyMap::HorizontalLock:
			fMapEditorControlsViewGroup.setHorizontalLock(v);
			break;

		case MapEditorPropertyMap::GridSnap:
			fMapEditorControlsViewGroup.setGridSnap(v);
			break;

		case MapEditorPropertyMap::TimeFlow:
			fMapEditorControlsViewGroup.setTimeFlow(v);
			break;

		default:
			break;
	}
}