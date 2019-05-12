#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/TextViewItem.h"


class EndGameViewGroup : public ViewGroup {
	TextViewItem fStatus;
	TextViewItem fPoints;
	TextViewItem fTime;

public:
	explicit EndGameViewGroup(const ViewAlignment& a);

	void setPoints(const std::string & p);
	void setTime(const std::string& s);
};