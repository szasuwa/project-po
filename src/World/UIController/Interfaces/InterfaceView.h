#pragma once
#include <vector>

#include "../../Interfaces/UIViewInterface.h"
#include "ViewGroup.h"


class InterfaceView : public UIViewInterface {
protected:
	std::vector<ViewGroup*> fGroupList;

public:
	InterfaceView(UIInterface& f) : UIViewInterface(f) {};
	virtual ~InterfaceView() {}
	virtual void updateView();
	virtual void update();
	virtual void draw();
};