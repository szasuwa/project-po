#pragma once
#include <vector>

#include "Interfaces/InterfaceView.h"
#include "Views/MainMenu.h"
#include "Views/GraphicalUserInterface.h"
#include "Views/MapEditorInterface.h"
#include "Views/DebugOverlay.h"
#include "InterfaceType.h"
#include "OverlayType.h"


class InterfaceController {
private:
	static InterfaceController* instance;

	InterfaceView* fInterfaces[(int)(InterfaceType::num_values)] = { nullptr };
	OverlayView* fOverlays[(int)(OverlayType::num_values)] = { nullptr };
	InterfaceView* fActiveView = nullptr;
	InterfaceType fActiveViewType = InterfaceType::num_values;

	InterfaceController();
	InterfaceController(const InterfaceController& o);

public:
	static InterfaceController& getInstance();
	~InterfaceController();

	void updateView();
	void update();
	void draw() const;

	void selectInterface(const InterfaceType & i);
	InterfaceType getSelectedInterfaceType() const;

	void toggleOverlayVisibility(const OverlayType & i);
	void setOverlayVisibility(const OverlayType& i, const bool& v);

};