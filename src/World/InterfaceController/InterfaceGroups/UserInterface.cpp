#include "UserInterface.h"
int UserInterface::fPoints = 0;

UserInterface::UserInterface() : InterfaceGroup()
{
}

UserInterface::UserInterface(const Alignment & a) : InterfaceGroup(a)
{
	fItemList.push_back(&fPointsBox);
}

void UserInterface::update()
{
	fPointsBox.setText(std::string("Points: " + std::to_string(fPoints)));
}

void UserInterface::setPoints(int p)
{
	fPoints = p;
}

