#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"


class UserViewGroup : public ViewGroup {
	TextViewItem fTime;
	TextViewItem fPoints;

public:
	explicit UserViewGroup(const ViewAlignment& a);

	void setPoints(const std::string & p);
	void setTime(const std::string& p);
};