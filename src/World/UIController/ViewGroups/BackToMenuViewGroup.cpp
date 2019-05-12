#include "BackToMenuViewGroup.h"
#include "../ViewActions/TextColorChangeViewAction.h"
#include "../ViewActions/InterfaceSelectionViewAction.h"


BackToMenuViewGroup::BackToMenuViewGroup(GameEngineInterface& f) : BackToMenuViewGroup(f, ViewAlignment::Left)
{
}

BackToMenuViewGroup::BackToMenuViewGroup(GameEngineInterface& f, const ViewAlignment& a) : ViewGroup(a)
{
	fBackToMenu.setText("Main Menu");
	fBackToMenu.setColor(TEXT_DEFAULT_COLOR);
	fBackToMenu.setOnClick(new InterfaceSelectionViewAction(f, InterfaceType::MainMenu));
	fBackToMenu.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fBackToMenu));
	fBackToMenu.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fBackToMenu));

	fItemList.push_back(&fBackToMenu);
}


