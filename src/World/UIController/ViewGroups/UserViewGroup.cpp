#include "UserViewGroup.h"


UserViewGroup::UserViewGroup(UIInterface& f) : UserViewGroup(f, ViewAlignment::Left)
{
}

UserViewGroup::UserViewGroup(UIInterface& f, const ViewAlignment& a) : ViewGroup(f, a), fPointsBox(f)
{
	fItemList.push_back(&fPointsBox);
}

void UserViewGroup::update()
{
	fPointsBox.setText(std::string("Points: " + std::to_string(fPoints)));
	ViewGroup::update();
}

void UserViewGroup::setPoints(int p)
{
	fPoints = p;
}

