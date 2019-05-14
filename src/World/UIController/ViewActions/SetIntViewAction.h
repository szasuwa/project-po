#pragma once
#include "ViewAction.h"


class SetIntViewAction : public ViewAction {
	int & fTarget;
	int fValue;

public:
	explicit SetIntViewAction(int& t, const int& v) : fTarget(t), fValue(v) {};
	virtual void operator() () { fTarget = fValue; };
};