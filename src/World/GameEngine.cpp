#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window), fFrame(Frame::getInstance()), fKeyController(KeyController::getInstance())
{
	fFrame.setWindow(fGameWindow);
}

void GameEngine::initGame()
{
	fGameWindow.setFramerateLimit(120);
	fMapController.load("map1");
	
	fInterface.updateView();
	fInterface.addInterface(InterfaceType::Debug, false);
	fInterface.addInterface(InterfaceType::Info);
	fInterface.addInterface(InterfaceType::MapEditor, false);
	fInterface.addInterface(InterfaceType::User);
	fInterface.addInterface(InterfaceType::Controls);
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
		fInterface.toggleInterfaceVisibility(InterfaceType::Debug);
	}

	
		
	if (fIsEditingMap) 
	{
		if (fKeyController.getKeyGroup(KeyBinding::MapEditorTime).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorTime).isPressed())
		{
			fTimeFlowEnabled = !fTimeFlowEnabled;
			MapEditorInterface::reportTimeFlowStatus(fTimeFlowEnabled);
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
			fInterface.setInterfaceVisibility(fIsEditingMap, InterfaceType::MapEditor);
			fInterface.setInterfaceVisibility(true, InterfaceType::Info);
			fMapController.stopEditing();
		}

		if (fKeyController.getKeyGroup(KeyBinding::MapEditorCancel).wasToggled() && fKeyController.getKeyGroup(KeyBinding::MapEditorCancel).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = true;
			fInterface.setInterfaceVisibility(fIsEditingMap, InterfaceType::MapEditor);
			fInterface.setInterfaceVisibility(true, InterfaceType::Info);
			fMapController.cancelEditing();
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
			MapEditorInterface::reportTimeFlowStatus(fTimeFlowEnabled);
			fInterface.setInterfaceVisibility(fIsEditingMap, InterfaceType::MapEditor);
			fInterface.setInterfaceVisibility(false, InterfaceType::Info);
			fMapController.startEditing();
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