#include "GameEngine.h"


GameEngine::GameEngine(FrameInterface& f, InputInterface& i, MapInterface& m, UIInterface& u)
 : GameEngineInterface(f,i,m,u)
{
	fMapI.setEngine(*this);
	fUiI.setEngine(*this);
}

void GameEngine::initGame()
{
	fUiI.updateView();
	fUiI.addUIView((unsigned int)InterfaceType::MainMenu);
}

void GameEngine::gameLoop()
{
	if (fFrameI.isOpen()) {
		initGame();
	}

	while (fFrameI.isOpen())
	{
		
		handleEvents();
		if (fFrameI.hasFocus()) {
			fInputI.update();
			handleTriggers();
			fFrameI.clear();

			fUiI.update();
			fUiI.draw();

			if (fTimeFlowEnabled)
				fMapI.updateMap();

			if (fUiI.isViewVisible((unsigned int)InterfaceType::MapEditor))
				fMapI.updateEditor();

			if (fUiI.isViewVisible((unsigned int)InterfaceType::MapEditor) || fUiI.isViewVisible((unsigned int)InterfaceType::Gui))
				fMapI.drawMap();
			
			fFrameI.display();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds((long)(fFrameI.getMaxFrameTime() * 1000)));
		}
		fFrameI.nextFrame();
	}
}

void GameEngine::handleTriggers()
{
	if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::Debug, true))
	{
		fUiI.toggleViewVisibility((unsigned int)InterfaceType::Debug);
	}
		
	if (fUiI.isViewVisible((unsigned int)InterfaceType::MapEditor)) 
	{
		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorTime, true))
		{
			fTimeFlowEnabled = !fTimeFlowEnabled;
			fUiI.setProperty((unsigned int)InterfaceType::MapEditor, MapEditorPropertyMap::TimeFlow, fTimeFlowEnabled ? "On" : "Off");
		}

		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorSave, true))
		{
			fMapI.saveEditedMap();
		}

		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorReset, true))
		{
			fMapI.resetEditedMap();
		}		

		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorExit, true))
		{
			fTimeFlowEnabled = true;
			fUiI.broadcastVisibilityChange(false);
			fUiI.setViewVisibility((unsigned int)InterfaceType::Gui, true);
			fMapI.endEdition();
		}

		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditorCancel, true))
		{
			fTimeFlowEnabled = true;
			fUiI.broadcastVisibilityChange(false);
			fUiI.setViewVisibility((unsigned int)InterfaceType::Gui, true);
			fMapI.cancelEdition();
		}
	}
	else if(fUiI.isViewVisible((unsigned int)InterfaceType::Gui))
	{
		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::ResetMap, true))
		{
			fMapI.resetMap();
		}

		if (fInputI.wasKeyToggled((unsigned int)KeyBindingIndex::MapEditor, true))
		{
			fTimeFlowEnabled = false;
			fUiI.broadcastVisibilityChange(false);
			fUiI.setViewVisibility((unsigned int)InterfaceType::MapEditor, true);
			fMapI.beginEdition();
		}
	}
}

void GameEngine::handleEvents() {
	sf::Event appEvent;
	while (fFrameI.pollEvent(appEvent))
	{
		switch (appEvent.type)
		{
		case sf::Event::GainedFocus:
			fFrameI.nextFrame();
			break;

		case sf::Event::Resized:
			fUiI.updateView();
			fFrameI.nextFrame();
			fFrameI.nextFrame();
			fMapI.updateCamera();
			break;

		case sf::Event::Closed:
			fFrameI.close();
			break;

		default:
			break;
		}
	}
}