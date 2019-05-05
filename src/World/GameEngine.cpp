#include "GameEngine.h"


GameEngine::GameEngine(FrameInterface& f, InputInterface& i, MapInterface& m, UIInterface& u) : fFrame(f), fInput(i), fMapController(m), fUiController(u)
{
}

void GameEngine::initGame()
{
	fUiController.updateView();
	fUiController.addUIView((unsigned int)InterfaceType::MainMenu);
}

void GameEngine::gameLoop()
{
	if (fFrame.isOpen()) {
		initGame();
	}

	while (fFrame.isOpen())
	{
		
		handleEvents();
		if (fFrame.hasFocus()) {
			fInput.update();
			handleTriggers();
			fFrame.clear();

			fUiController.update();
			fUiController.draw();

			if (fTimeFlowEnabled)
				fMapController.updateMap();

			if (fUiController.isViewVisible((unsigned int)InterfaceType::MapEditor))
				fMapController.updateEditor();

			if (fUiController.isViewVisible((unsigned int)InterfaceType::MapEditor) || fUiController.isViewVisible((unsigned int)InterfaceType::Gui))
				fMapController.drawMap();
			
			fFrame.display();
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
	if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::Debug, true))
	{
		fUiController.toggleViewVisibility((unsigned int)InterfaceType::Debug);
	}
		
	if (fUiController.isViewVisible((unsigned int)InterfaceType::MapEditor)) 
	{
		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorTime, true))
		{
			fTimeFlowEnabled = !fTimeFlowEnabled;
			//MapEditorControlsViewGroup::reportTimeFlowStatus(fTimeFlowEnabled);
		}

		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorSave, true))
		{
			fMapController.saveEditedMap();
		}

		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorReset, true))
		{
			fMapController.resetEditedMap();
		}		

		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorExit, true))
		{
			fTimeFlowEnabled = true;
			fUiController.broadcastVisibilityChange(false);
			fUiController.setViewVisibility((unsigned int)InterfaceType::Gui, true);
			fMapController.endEdition();
		}

		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorCancel, true))
		{
			fTimeFlowEnabled = true;
			fUiController.broadcastVisibilityChange(false);
			fUiController.setViewVisibility((unsigned int)InterfaceType::Gui, true);
			fMapController.cancelEdition();
		}
	}
	else if(fUiController.isViewVisible((unsigned int)InterfaceType::Gui))
	{
		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::ResetMap, true))
		{
			fMapController.resetMap();
		}

		if (fInput.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditor, true))
		{
			fTimeFlowEnabled = false;
			fUiController.broadcastVisibilityChange(false);
			fUiController.setViewVisibility((unsigned int)InterfaceType::MapEditor, true);
			fMapController.beginEdition();
		}
	}
}

void GameEngine::handleEvents() {
	sf::Event appEvent;
	while (fFrame.pollEvent(appEvent))
	{
		switch (appEvent.type)
		{
		case sf::Event::GainedFocus:
			fFrame.nextFrame();
			break;

		case sf::Event::Resized:
			fUiController.updateView();
			fFrame.nextFrame();
			fFrame.nextFrame();
			fMapController.updateCamera();
			break;

		case sf::Event::Closed:
			fFrame.close();
			break;

		default:
			break;
		}
	}
}