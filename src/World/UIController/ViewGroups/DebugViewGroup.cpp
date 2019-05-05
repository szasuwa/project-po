#include "DebugViewGroup.h"

DebugViewGroup::DebugViewGroup(UIInterface& f) : DebugViewGroup(f, ViewAlignment::Left)
{
}

DebugViewGroup::DebugViewGroup(UIInterface& f, const ViewAlignment& a) : ViewGroup(f, a), fFrame(fUIInterface.getFrame()), fVersion(f), fFpsMeter(f), fSeparator(f)
{
	fVersion.setText("Version: " + GAME_VERSION);

	fItemList.push_back(&fVersion);
	fItemList.push_back(&fFpsMeter);
	fItemList.push_back(&fSeparator);
}

void DebugViewGroup::update()
{
	fFpsMeter.setText(std::to_string(fFrame.getFrameRate()) + " FPS");
	ViewGroup::update();
}