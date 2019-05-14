#include "VersionViewGroup.h"


VersionViewGroup::VersionViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fVersion.setText("Version: " + GAME_VERSION);
	fCopyright.setText(AUTHOR);

	fItemList.push_back(&fCopyright);
	fItemList.push_back(&fVersion);
}