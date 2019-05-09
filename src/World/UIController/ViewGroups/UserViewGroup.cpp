#include "UserViewGroup.h"


UserViewGroup::UserViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fItemList.push_back(&fPointsBox);
}

void UserViewGroup::update(GameEngineInterface& f)
{
	fPointsBox.setText(std::string("Points: " + std::to_string(fPoints)));
	ViewGroup::update(f);
}

void UserViewGroup::setPoints(int p)
{
	fPoints = p;
}

