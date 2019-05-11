#pragma once
class ViewAction {
public:
	ViewAction() {};
	virtual ~ViewAction() {};
	virtual void operator() () = 0;
};