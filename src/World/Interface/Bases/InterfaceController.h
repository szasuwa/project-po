#pragma once
#include <vector>

#include "InterfaceGroup.h"


class InterfaceController {
	std::vector<InterfaceGroup*> fInterfaceGroups;
	float fLeftHeight;
	float fRightHeight;
	float fCenterHeight;

public:
	void update();
	void draw(sf::RenderWindow &window);
	void addGroup(InterfaceGroup* grp);
};