#include "InterfaceController.h"


InterfaceController::~InterfaceController() 
{
	for (InterfaceView* item : fInterfaces)
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
	for (InterfaceView* item : fInterfaces)
	{
		if (item != nullptr) 
		{
			item->update();	
		}
	}

	for (OverlayView* item : fOverlays)
	{
		if (item != nullptr)
		{
			item->update();
		}
	}
}

void InterfaceController::draw() const {
	if (fActiveView != nullptr) 
	{
		fActiveView->draw();
	}

	for (OverlayView* item : fOverlays)
	{
		if (item != nullptr)
		{
			item->draw();
		}
	}
}

void InterfaceController::selectInterface(const InterfaceType & i)
{
	switch (i)
	{
		case InterfaceType::MainMenu:
			if(fInterfaces[(int)i] == nullptr)
				fInterfaces[(int)i] = new MainMenu();
			break;
		
		case InterfaceType::Gui:
			if (fInterfaces[(int)i] == nullptr)
				fInterfaces[(int)i] = new GraphicalUserInterface();
			break;

		case InterfaceType::MapEditor:
			if (fInterfaces[(int)i] == nullptr)
				fInterfaces[(int)i] = new MapEditorInterface();
			break;

		default:
			fActiveView = nullptr;
			return;
	}
	fActiveView = fInterfaces[(int)i];
}

void InterfaceController::toggleOverlayVisibility(const OverlayType& i)
{
	switch (i)
	{
		case OverlayType::Debug:
			if (fOverlays[(int)i] == nullptr)
				fOverlays[(int)i] = new DebugOverlay();

			fOverlays[(int)i]->toggleVisibility();
			break;
	default:
		return;
	}
}

void InterfaceController::setOverlayVisibility(const OverlayType& i, const bool & v)
{
	switch (i)
	{
	case OverlayType::Debug:
		if (fOverlays[(int)i] == nullptr)
			fOverlays[(int)i] = new DebugOverlay();

		fOverlays[(int)i]->setVisibility(v);
		break;
	default:
		return;
	}
}