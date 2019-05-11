#pragma once
#include "../ViewItems/TextViewItem.h"


class SetPointerViewAction : public ViewAction {
	void*&  fTarget;
	void* fValue;

public:
	explicit SetPointerViewAction(void*& t, void* v) : fTarget(t), fValue(v) {};
	virtual void operator() () { fTarget = fValue; };
};