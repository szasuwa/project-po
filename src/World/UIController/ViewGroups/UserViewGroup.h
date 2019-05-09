#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"


class UserViewGroup : public ViewGroup {
	TextViewItem fPointsBox;
	std::string fPoints = "0";

public:
	explicit UserViewGroup(const ViewAlignment& a);

	void update(GameEngineInterface& f);

	void setPoints(const std::string & p);
};