#include "DebugInterface.h"


DebugInterface::DebugInterface(const Alignment & a) : InterfaceGroup(a)
{
	fVersion.setText("Version: " + GAME_VERSION);

	fItemList.push_back(&fVersion);
	fItemList.push_back(&fFpsMeter);
}

void DebugInterface::update() 
{
	fFpsMeter.setText(std::to_string((Frame::getInstance()).getFrameRate()) + " FPS");
}