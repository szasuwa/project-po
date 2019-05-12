#include "EndGameViewGroup.h"


EndGameViewGroup::EndGameViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fStatus.setText("Level complete");
	fStatus.setColor(TEXT_SELECTED_COLOR);
	setPoints("0");
	setTime("00:00.00");

	fItemList.push_back(&fStatus);
	fItemList.push_back(&fTime);
	fItemList.push_back(&fPoints);
}

void EndGameViewGroup::setPoints(const std::string & p)
{
	fPoints.setText("Points: "+p);
}

void EndGameViewGroup::setTime(const std::string& p)
{
	fTime.setText("Time: " + p);
}


