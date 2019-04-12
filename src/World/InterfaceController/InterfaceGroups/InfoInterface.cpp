#include "InfoInterface.h"

InfoInterface::InfoInterface() : InterfaceGroup() 
{
}

InfoInterface::InfoInterface(const Alignment & a) : InterfaceGroup(a) 
{
	fMapEditorKey.setText(KeyController::getInstance().getKeyGroup(KeyController::MapEditor).toString() + " Map Editor");
	fDebugKey.setText(KeyController::getInstance().getKeyGroup(KeyController::Debug).toString() + " Debug");

	fItemList.push_back(&fMapEditorKey);
	fItemList.push_back(&fDebugKey);
}

void InfoInterface::update() 
{
}