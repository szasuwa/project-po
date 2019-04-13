#pragma once 
#include "InterfaceGroup.h"
#include "../InterfaceItems/InterfaceText.h"


class UserInterface : public InterfaceGroup {
	InterfaceText fPointsBox;
	static int fPoints;

public:
	explicit UserInterface(const Alignment & a = Alignment::Left);
	void update();

	static void setPoints(int p);
};