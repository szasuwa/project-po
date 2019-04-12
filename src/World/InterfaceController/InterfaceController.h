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
	std::vector<InterfaceGroup*> fInterfaceGroups = std::vector<InterfaceGroup*>(num_values, nullptr);

public:
	void update();
	void draw() const;
	int addInterface(const InterfaceType & i);
	void setInterfaceVisibility(const bool & v, const InterfaceType & i);
};