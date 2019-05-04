#include "UserViewGroup.h"
int UserViewGroup::fPoints = 0;

UserViewGroup::UserViewGroup() : UserViewGroup(ViewAlignment::Left)
{
}

UserViewGroup::UserViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fItemList.push_back(&fPointsBox);
}

void UserViewGroup::update()
{
	fPointsBox.setText(std::string("Points: " + std::to_string(fPoints)));
}

void UserViewGroup::setPoints(int p)
{
	fPoints = p;
}

