#pragma once
#include <vector>

#include "InterfaceGroups/InterfaceGroup.h"
#include "InterfaceGroups/UserInterface.h"
#include "InterfaceGroups/InfoInterface.h"
#include "InterfaceGroups/DebugInterface.h"
#include "InterfaceGroups/MapEditorInterface.h"


class InterfaceController {
public:
	enum InterfaceType {
		User,
		Info,
		Debug,
		MapEditor,
		num_values
	};

private:
	InterfaceGroup* fInterfaceGroups[num_values];

public:
	~InterfaceController();
	void updateView();
	void update();
	void draw() const;
	void addInterface(const InterfaceType & i, const bool & v = true);
	void setInterfaceVisibility(const bool & v, const InterfaceType & i);
	void toggleInterfaceVisibility(const InterfaceType & i);
};