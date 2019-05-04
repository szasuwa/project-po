#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"


class UserViewGroup : public ViewGroup {
	TextViewItem fPointsBox;
	static int fPoints;

public:
	UserViewGroup();
	explicit UserViewGroup(const ViewAlignment& a);

	void update();

	static void setPoints(int p);
};