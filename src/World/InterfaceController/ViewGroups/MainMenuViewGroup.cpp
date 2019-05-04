#include "MainMenuViewGroup.h"


MainMenuViewGroup::MainMenuViewGroup() : MainMenuViewGroup(ViewAlignment::Left)
{
}

MainMenuViewGroup::MainMenuViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fStartButton.setText("Start");
	fItemList.push_back(&fStartButton);
}

void MainMenuViewGroup::update()
{
}

