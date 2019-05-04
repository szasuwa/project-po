#pragma once
#include <vector>

#include "ViewGroup.h"


class InterfaceView {
protected:
	std::vector<ViewGroup*> fGroupList;

public:
	virtual void updateView();
	virtual void update();
	virtual void draw();
};