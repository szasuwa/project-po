#include "DebugViewGroup.h"

DebugViewGroup::DebugViewGroup() : DebugViewGroup(ViewAlignment::Left)
{
}

DebugViewGroup::DebugViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fVersion.setText("Version: " + GAME_VERSION);

	fItemList.push_back(&fVersion);
	fItemList.push_back(&fFpsMeter);
	fItemList.push_back(&fSeparator);
}

void DebugViewGroup::update()
{
	fFpsMeter.setText(std::to_string((Frame::getInstance()).getFrameRate()) + " FPS");
}