#pragma once
#include "../Interfaces/UIInterface.h"
#include "Interfaces/InterfaceView.h"
#include "InterfaceType.h"
#include "Views/MainMenu.h"
#include "Views/DebugInterface.h"
#include "Views/GraphicalUserInterface.h"
#include "Views/MapEditorInterface.h"
#include "Views/MapSelection.h"



class UIController : public UIInterface {
public:
	UIController(FrameInterface& f, InputInterface& i, MapInterface& m);
	~UIController();

	virtual void init();

	virtual void updateView();
	virtual void update();
	virtual void draw() const;

	virtual unsigned int addUIView(UIViewInterface* i);
	virtual void addUIView(const unsigned int& i);

	virtual void removeUIView(const unsigned int& i);
	virtual void removeAllUIViews();
	virtual unsigned int removeAllUIViewsBut(const unsigned int& i);

	virtual void destroyUIView(const unsigned int& i);
	virtual void destroyAllUIViews();
	virtual unsigned int destroyAllUIViewsBut(const unsigned int& i);

	virtual UIViewInterface * getUIView(const unsigned int& i);

	virtual void setViewVisibility(const unsigned int& i, const bool& v);
	virtual void toggleViewVisibility(const unsigned int& i);
	virtual bool isViewVisible(const unsigned int& i);
	virtual void broadcastVisibilityChange(const bool & v);
};