#include "InterfaceController.h"


InterfaceController::~InterfaceController() 
{
	for (InterfaceGroup * item : fInterfaceGroups)
	{
		delete item;
	}
}

void InterfaceController::updateView()
{
	Frame & f = Frame::getInstance();
	sf::View view(sf::FloatRect(0,0, f.getFrameWidth(), f.getFrameHeight()));
	f.updateView(view, Frame::FrameLayer::Interface);
}

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

void InterfaceController::addInterface(const InterfaceType & i)
{
	switch (i)
	{
		case User:
			fInterfaceGroups[i] = new UserInterface(InterfaceGroup::Alignment::Center);
			break;
		case Info:
			fInterfaceGroups[i] = new InfoInterface(InterfaceGroup::Alignment::Left);
			break;
		case Debug:
			fInterfaceGroups[i] = new DebugInterface(InterfaceGroup::Alignment::Right);
			break;
		case MapEditor:
			fInterfaceGroups[i] = new MapEditorInterface(InterfaceGroup::Alignment::Left);
			break;
		default:
			return;
	}
}

void InterfaceController::setInterfaceVisibility(const bool & v, const InterfaceType & i)
{
	if (i < 0 && i >= InterfaceController::num_values)
		return;

	if (fInterfaceGroups[i] == nullptr)
		return;

	fInterfaceGroups[i]->setVisibility(v);
}