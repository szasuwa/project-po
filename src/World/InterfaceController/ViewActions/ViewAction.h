#pragma once
class ViewAction {
public:
	ViewAction() {};
	virtual void operator() () = 0;
};