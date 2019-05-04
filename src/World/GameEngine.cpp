#include "GameEngine.h"


GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window), fFrame(Frame::getInstance()), fKeyController(KeyController::getInstance()), fMouseController(MouseController::getInstance())
{
	fFrame.setWindow(fGameWindow);
}

void GameEngine::initGame()
{
	//fMapController.load("map1");
	
	fInterface.setOverlayVisibility(OverlayType::Debug, false);
	fInterface.selectInterface(InterfaceType::MainMenu);
	fInterface.selectInterface(InterfaceType::Gui);
	fInterface.updateView();
}

void GameEngine::gameLoop()
{
	if (fGameWindow.isOpen()) {
		initGame();
	}

	while (fGameWindow.isOpen())
	{
		handleTriggers();
		handleEvents();
		if (fGameWindow.hasFocus()) {
			fGameWindow.clear();

			fMouseController.update();

			fInterface.update();
			fInterface.draw();

			if(fTimeFlowEnabled)
				fMapController.updateMap();

			if (fIsEditingMap)
				fMapController.updateEditor();

			fMapController.drawMap();
			fGameWindow.display();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long)(fFrame.getMaxFrameTime() * 1000)));
		}
		fFrame.nextFrame();
	}
}

void GameEngine::handleTriggers()
{
	if (fKeyController.getKeyGroup(KeyBinding::Debug).wasToggled() && fKeyController.getKeyGroup(KeyBinding::Debug).isPressed())
	{
		fInterface.toggleOverlayVisibility(OverlayType::Debug);
	}
		
	if (fIsEditingMap) 
	{
		if (fKeyController.getKeyGroup(KeyBinding::MapEditorTime).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorTime).isPressed())
		{
			fTimeFlowEnabled = !fTimeFlowEnabled;
			MapEditorControlsViewGroup::reportTimeFlowStatus(fTimeFlowEnabled);
		}

		if (fKeyController.getKeyGroup(KeyBinding::MapEditorSave).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorSave).isPressed())
		{
			fMapController.saveEditedMap();
		}

		if (fKeyController.getKeyGroup(KeyBinding::MapEditorReset).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorReset).isPressed())
		{
			fMapController.resetEditedMap();
		}		

		if (fKeyController.getKeyGroup(KeyBinding::MapEditorExit).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorExit).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = true;
			fInterface.selectInterface(InterfaceType::Gui);
			fMapController.endEdition();
		}

		if (fKeyController.getKeyGroup(KeyBinding::MapEditorCancel).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorCancel).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = true;
			fInterface.selectInterface(InterfaceType::Gui);
			fMapController.cancelEdition();
		}
	}
	else 
	{
		if (fKeyController.getKeyGroup(KeyBinding::ResetMap).wasToggled() && fKeyController.getKeyGroup(KeyBinding::ResetMap).isPressed())
		{
			fMapController.resetMap();
		}

		if (fKeyController.getKeyGroup(KeyBinding::MapEditor).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditor).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = false;
			fInterface.selectInterface(InterfaceType::MapEditor);
			fMapController.beginEdition();
		}
	}
}

void GameEngine::handleEvents() {
	sf::Event appEvent;
	while (fGameWindow.pollEvent(appEvent))
	{
		switch (appEvent.type)
		{
		case sf::Event::GainedFocus:
			fFrame.nextFrame();
			break;

		case sf::Event::Resized:
			fInterface.updateView();
			fFrame.nextFrame();
			fFrame.nextFrame();
			fMapController.updateCamera();
			break;

		case sf::Event::Closed:
			fGameWindow.close();
			break;

		default:
			break;
		}
	}
}