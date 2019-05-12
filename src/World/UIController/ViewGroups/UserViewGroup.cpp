#include "UserViewGroup.h"


UserViewGroup::UserViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	setTime("00:00");
	setPoints("0");

	fItemList.push_back(&fTime);
	fItemList.push_back(&fPoints);
}

void UserViewGroup::setPoints(const std::string & p)
{
	fPoints.setText(std::string("Points: " + p));
}

void UserViewGroup::setTime(const std::string& p)
{
	fTime.setText(std::string("Time: " + p));
}

