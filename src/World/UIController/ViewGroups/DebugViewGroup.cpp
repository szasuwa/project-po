#include "DebugViewGroup.h"

DebugViewGroup::DebugViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fVersion.setText("Version: " + GAME_VERSION);

	fItemList.push_back(&fVersion);
	fItemList.push_back(&fFpsMeter);
	fItemList.push_back(&fSeparator);
}

void DebugViewGroup::update(UIInterface& f)
{
	fFpsMeter.setText(std::to_string(f.getFrame().getFrameRate()) + " FPS");
	ViewGroup::update(f);
}