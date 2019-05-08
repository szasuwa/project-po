#pragma once
#include <vector>

#include "../../Interfaces/UIViewInterface.h"
#include "ViewGroup.h"

class InterfaceView : public UIViewInterface {
protected:
	std::vector<ViewGroup*> fGroupList;
	std::vector<std::string> fPropertyList;

public:
	virtual ~InterfaceView() {}
	virtual void updateView(UIInterface& f);
	virtual void update(UIInterface& f);
	virtual void draw(UIInterface& f);
	
	virtual std::string getProperty(const unsigned int& i);
	virtual void setProperty(const unsigned int& i, const std::string& v);
};