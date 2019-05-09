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
	virtual void updateView(GameEngineInterface& f);
	virtual void update(GameEngineInterface& f);
	virtual void draw(GameEngineInterface& f);
	
	virtual std::string getProperty(const unsigned int& i);
	virtual void setProperty(const unsigned int& i, const std::string& v);
};