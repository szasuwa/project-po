#pragma once 
#include "Bases/InterfaceGroup.h"
#include "Bases/InterfaceText.h"


class Gui : public InterfaceGroup {
	InterfaceText fPointsBox;
	static int fPoints;

public:
	Gui();
	explicit Gui(Alignment align);
	void update();

	static void setPoints(int p);
};