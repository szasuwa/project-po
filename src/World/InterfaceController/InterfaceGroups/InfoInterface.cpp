#include "InfoInterface.h"

InfoInterface::InfoInterface(const Alignment & a) : InterfaceGroup(a) 
{
	fMapEditorKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::MapEditor).toString() + " Map Editor");
	fDebugKey.setText(KeyController::getInstance().getKeyGroup(KeyBinding::Debug).toString() + " Debug");

	fItemList.push_back(&fMapEditorKey);
	fItemList.push_back(&fDebugKey);
}

void InfoInterface::update() 
{
}