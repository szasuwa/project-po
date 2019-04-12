#pragma once
#include <vector>

#include "InterfaceGroup.h"


class InterfaceController {
	std::vector<InterfaceGroup*> fInterfaceGroups;

public:
	void update();
	void draw(sf::RenderWindow &window);
	void addGroup(InterfaceGroup* grp);
};