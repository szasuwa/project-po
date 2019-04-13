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
				case InterfaceGroup::Alignment::Left:
					item->calculatePositions(fLeftHeight);
					fLeftHeight += item->calculateHeight();
					break;
				case InterfaceGroup::Alignment::Right:
					item->calculatePositions(fRightHeight);
					fRightHeight += item->calculateHeight();
					break;
				case InterfaceGroup::Alignment::Center:
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

void InterfaceController::addInterface(const InterfaceType & i, const bool & v)
{
	switch (i)
	{
		case InterfaceType::User:
			fInterfaceGroups[(int)i] = new UserInterface(InterfaceGroup::Alignment::Center);
			break;
		case InterfaceType::Info:
			fInterfaceGroups[(int)i] = new InfoInterface(InterfaceGroup::Alignment::Left);
			break;
		case InterfaceType::Debug:
			fInterfaceGroups[(int)i] = new DebugInterface(InterfaceGroup::Alignment::Right);
			break;
		case InterfaceType::MapEditor:
			fInterfaceGroups[(int)i] = new MapEditorInterface(InterfaceGroup::Alignment::Left);
			break;
		case InterfaceType::Controls:
			fInterfaceGroups[(int)i] = new ControlsInterface(InterfaceGroup::Alignment::Right);
			break;
		default:
			return;
	}
	fInterfaceGroups[(int)i]->setVisibility(v);
}

void InterfaceController::setInterfaceVisibility(const bool & v, const InterfaceType & i)
{
	if (i == InterfaceType::num_values || fInterfaceGroups[(int)i] == nullptr)
		return;

	fInterfaceGroups[(int)i]->setVisibility(v);
}

void InterfaceController::toggleInterfaceVisibility(const InterfaceType & i)
{
	if (i == InterfaceType::num_values || fInterfaceGroups[(int)i] == nullptr)
		return;

	fInterfaceGroups[(int)i]->toggleVisibility();
}