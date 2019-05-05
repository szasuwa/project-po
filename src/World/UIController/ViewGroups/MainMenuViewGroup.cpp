#include "MainMenuViewGroup.h"
#include "../ViewActions/MapSelectionViewAction.h"
#include "../ViewActions/TextColorChangeViewAction.h"


MainMenuViewGroup::MainMenuViewGroup(UIInterface& f) : MainMenuViewGroup(f, ViewAlignment::Left)
{
}

MainMenuViewGroup::MainMenuViewGroup(UIInterface& f, const ViewAlignment& a) : ViewGroup(f, a), fStartButton(f)
{
	fStartButton.setText("Start");
	fStartButton.setOnClick(new MapSelectionViewAction(fUIInterface, (unsigned int)InterfaceType::MainMenu, "map1"));
	fStartButton.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fStartButton));
	fStartButton.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fStartButton));
	fItemList.push_back(&fStartButton);
}