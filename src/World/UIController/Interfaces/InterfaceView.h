#pragma once
#include <vector>

#include "../../Interfaces/UIViewInterface.h"
#include "ViewGroup.h"


class InterfaceView : public UIViewInterface {
protected:
	std::vector<ViewGroup*> fGroupList;

public:
	virtual ~InterfaceView() {}
	virtual void updateView(UIInterface& f);
	virtual void update(UIInterface& f);
	virtual void draw(UIInterface& f);
};