#pragma once 
#include "Base/InterfaceGroup.h"
#include "Base/InterfaceText.h"


class Gui : public InterfaceGroup {
	InterfaceText fPointsBox;
	static int fPoints;

public:
	Gui();
	explicit Gui(Alignment align);
	void update();

	static void setPoints(int p);
};