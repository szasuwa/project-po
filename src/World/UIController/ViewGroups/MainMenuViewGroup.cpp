#include "MainMenuViewGroup.h"
#include "../ViewActions/MapSelectionViewAction.h"
#include "../ViewActions/TextColorChangeViewAction.h"

MainMenuViewGroup::MainMenuViewGroup(GameEngineInterface& f) : MainMenuViewGroup(f, ViewAlignment::Left)
{
}

MainMenuViewGroup::MainMenuViewGroup(GameEngineInterface& f, const ViewAlignment& a) : ViewGroup(a)
{
	fStartButton.setText("Start");
	fStartButton.setOnClick(new MapSelectionViewAction(f, (unsigned int)InterfaceType::MainMenu, "map1"));
	fStartButton.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fStartButton));
	fStartButton.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fStartButton));
	fItemList.push_back(&fStartButton);
}