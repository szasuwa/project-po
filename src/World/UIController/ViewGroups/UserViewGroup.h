#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"


class UserViewGroup : public ViewGroup {
	TextViewItem fPointsBox;
	int fPoints;

public:
	explicit UserViewGroup(const ViewAlignment& a);

	void update(UIInterface& f);

	void setPoints(int p);
};