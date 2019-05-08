#pragma once
#include <vector>
#include "UIViewInterface.h"
#include "FrameInterface.h"
#include "InputInterface.h"
#include "MapInterface.h"


class UIInterface {
protected:
	FrameInterface& fFrame;
	InputInterface& fInput;
	MapInterface& fMap;

	std::vector<UIViewInterface*> fUIViews;

public:
	UIInterface(FrameInterface& f, InputInterface& i, MapInterface& m) : fFrame(f), fInput(i), fMap(m) {};
	virtual ~UIInterface() {};

	FrameInterface& getFrame() { return fFrame; }
	InputInterface& getInput() { return fInput; }
	MapInterface& getMap() { return fMap; }

	virtual void updateView() = 0;
	virtual void update() = 0;
	virtual void draw() const = 0;

	virtual unsigned int addUIView(UIViewInterface* i) = 0;
	virtual void addUIView(const unsigned int& i) = 0;

	virtual void removeUIView(const unsigned int& i) = 0;
	virtual void removeAllUIViews() = 0;
	virtual unsigned int removeAllUIViewsBut(const unsigned int& i) = 0;

	virtual void destroyUIView(const unsigned int& i) = 0;
	virtual void destroyAllUIViews() = 0;
	virtual unsigned int destroyAllUIViewsBut(const unsigned int& i) = 0;

	virtual UIViewInterface * getUIView(const unsigned int & i) = 0;
	
	virtual void setViewVisibility(const unsigned int& i, const bool & v) = 0;
	virtual void toggleViewVisibility(const unsigned int& i) = 0;
	virtual bool isViewVisible(const unsigned int& i) = 0;
	virtual void broadcastVisibilityChange(const bool& v) = 0;

	virtual std::string getProperty(const unsigned int& view, const unsigned int& id) = 0;
	virtual void setProperty(const unsigned int& view, const unsigned int& id, const std::string& v) = 0;
};