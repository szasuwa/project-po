#include "GameEngine.h"

GameEngine::GameEngine(sf::RenderWindow &window) : fGameWindow(window), fFrame(Frame::getInstance()), fKeyController(KeyController::getInstance())
{
	fFrame.setWindow(fGameWindow);
}

void GameEngine::initGame()
{
	fGameWindow.setFramerateLimit(120);
	fMapManager.load("map1");
	
	fInterface.updateView();
	fInterface.addInterface(InterfaceController::InterfaceType::Debug, false);
	fInterface.addInterface(InterfaceController::InterfaceType::Info);
	fInterface.addInterface(InterfaceController::InterfaceType::MapEditor, false);
	fInterface.addInterface(InterfaceController::InterfaceType::User);
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
				fMapManager.updateMap();

			if (fIsEditingMap)
				fMapManager.updateEditor();

			fMapManager.drawMap();
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
	if (fKeyController.getKeyGroup(KeyController::Debug).wasToggled() && fKeyController.getKeyGroup(KeyController::Debug).isPressed())
	{
		fInterface.toggleInterfaceVisibility(InterfaceController::InterfaceType::Debug);
	}

	
		
	if (fIsEditingMap) 
	{
		if (fKeyController.getKeyGroup(KeyController::MapEditorTime).wasToggled() && fKeyController.getKeyGroup(KeyController::MapEditorTime).isPressed())
		{
			fTimeFlowEnabled = !fTimeFlowEnabled;
			MapEditorInterface::reportTimeFlowStatus(fTimeFlowEnabled);
		}

		if (fKeyController.getKeyGroup(KeyController::MapEditorSave).wasToggled() && fKeyController.getKeyGroup(KeyController::MapEditorSave).isPressed())
		{
			fMapManager.saveEditedMap();
		}

		if (fKeyController.getKeyGroup(KeyController::MapEditorReset).wasToggled() && fKeyController.getKeyGroup(KeyController::MapEditorReset).isPressed())
		{
			fMapManager.resetEditedMap();
		}		

		if (fKeyController.getKeyGroup(KeyController::MapEditorExit).wasToggled() && fKeyController.getKeyGroup(KeyController::MapEditorExit).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = true;
			fInterface.setInterfaceVisibility(fIsEditingMap, InterfaceController::InterfaceType::MapEditor);
			fInterface.setInterfaceVisibility(true, InterfaceController::InterfaceType::Info);
			fMapManager.stopEditing();
		}

		if (fKeyController.getKeyGroup(KeyController::MapEditorCancel).wasToggled() && fKeyController.getKeyGroup(KeyController::MapEditorCancel).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = true;
			fInterface.setInterfaceVisibility(fIsEditingMap, InterfaceController::InterfaceType::MapEditor);
			fInterface.setInterfaceVisibility(true, InterfaceController::InterfaceType::Info);
			fMapManager.cancelEditing();
		}
	}
	else 
	{
		if (fKeyController.getKeyGroup(KeyController::MapEditor).wasToggled() && fKeyController.getKeyGroup(KeyController::MapEditor).isPressed())
		{
			fIsEditingMap = !fIsEditingMap;
			fTimeFlowEnabled = false;
			MapEditorInterface::reportTimeFlowStatus(fTimeFlowEnabled);
			fInterface.setInterfaceVisibility(fIsEditingMap, InterfaceController::InterfaceType::MapEditor);
			fInterface.setInterfaceVisibility(false, InterfaceController::InterfaceType::Info);
			fMapManager.startEditing();
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
			fMapManager.updateCamera();
			break;

		case sf::Event::Closed:
			fGameWindow.close();
			break;

		default:
			break;
		}
	}
}