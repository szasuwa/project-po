#include "MainMenuViewGroup.h"
#include "../ViewActions/MapSelectionViewAction.h"
#include "../ViewActions/TextColorChangeViewAction.h"


MainMenuViewGroup::MainMenuViewGroup() : MainMenuViewGroup(ViewAlignment::Left)
{
}

MainMenuViewGroup::MainMenuViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fStartButton.setText("Start");
	fStartButton.setOnClick(new MapSelectionViewAction("map1"));
	fStartButton.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fStartButton));
	fStartButton.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fStartButton));
	fItemList.push_back(&fStartButton);
}