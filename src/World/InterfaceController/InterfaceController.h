#pragma once
#include <vector>

#include "InterfaceGroups/InterfaceGroup.h"
#include "InterfaceGroups/UserInterface.h"
#include "InterfaceGroups/InfoInterface.h"
#include "InterfaceGroups/DebugInterface.h"
#include "InterfaceGroups/MapEditorInterface.h"
#include "InterfaceGroups/ControlsInterface.h"
#include "InterfaceType.h"


class InterfaceController {
private:
	InterfaceGroup* fInterfaceGroups[(int)(InterfaceType::num_values)];

public:
	~InterfaceController();
	void updateView();
	void update();
	void draw() const;
	void addInterface(const InterfaceType & i, const bool & v = true);
	void setInterfaceVisibility(const bool & v, const InterfaceType & i);
	void toggleInterfaceVisibility(const InterfaceType & i);
};