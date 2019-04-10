#include "InterfaceController.h"

void InterfaceController::update() {
	fLeftHeight = fCenterHeight = fRightHeight = 1;

	for (InterfaceGroup * item : fInterfaceGroups) {
		if (item != nullptr && item->getVisibility()) {
			item->update();

			switch (item->getAlignment())
			{
			case InterfaceGroup::Left:
				item->calculatePositions(fLeftHeight);
				fLeftHeight += item->calculateHeight();
				break;
			case InterfaceGroup::Right:
				item->calculatePositions(fRightHeight);
				fRightHeight += item->calculateHeight();
				break;
			case InterfaceGroup::Center:
				item->calculatePositions(fCenterHeight);
				fCenterHeight += item->calculateHeight();
				break;
			default:
				break;
			}			
		}
	}
}
void InterfaceController::draw(sf::RenderWindow &window) {
	for (InterfaceGroup * item : fInterfaceGroups) {
		if (item != nullptr) {
			item->drawGroup(window);
		}
	}
}

void InterfaceController::addGroup(InterfaceGroup* grp) {
	fInterfaceGroups.push_back(grp);
}
