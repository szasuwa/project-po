#pragma once
#include <SFML/Graphics/Color.hpp>

#include "../ViewItems/TextViewItem.h"


class SetBoolViewAction : public ViewAction {
	bool & fTarget;
	bool fValue;

public:
	explicit SetBoolViewAction(bool& t, const bool& v) : fTarget(t), fValue(v) {};
	virtual void operator() () { fTarget = fValue; };
};