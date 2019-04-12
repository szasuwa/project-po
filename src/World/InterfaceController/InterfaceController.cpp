#include "InterfaceController.h"

void InterfaceController::update() 
{
	float fLeftHeight, fCenterHeight, fRightHeight;
	fLeftHeight = fCenterHeight = fRightHeight = 1;

	for (InterfaceGroup * item : fInterfaceGroups) 
	{
		if (item != nullptr && item->getVisibility()) 
		{
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
void InterfaceController::draw() const {
	for (InterfaceGroup * item : fInterfaceGroups) 
	{
		if (item != nullptr) 
		{
			item->drawGroup();
		}
	}
}

int InterfaceController::addInterface(const InterfaceType & i)
{
	switch (i)
	{
		case User:
			fInterfaceGroups[i] = &UserInterface(InterfaceGroup::Alignment::Center);;
			break;
		case Info:
			fInterfaceGroups[i] = &InfoInterface(InterfaceGroup::Alignment::Left);
			break;
		case Debug:
			fInterfaceGroups[i] = &DebugInterface(InterfaceGroup::Alignment::Right);
			break;
		case MapEditor:
			fInterfaceGroups[i] = &MapEditorInterface(InterfaceGroup::Alignment::Left);
			break;
		default:
			return;
	}
}

void InterfaceController::setInterfaceVisibility(const bool & v, const InterfaceType & i)
{
	if (i == InterfaceController::num_values)
		return;

	if (fInterfaceGroups[i] == nullptr)
		return;

	fInterfaceGroups[i]->setVisibility(v);
}