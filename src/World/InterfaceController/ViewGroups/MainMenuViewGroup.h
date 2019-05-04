#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/ButtonViewItem.h"


class MainMenuViewGroup : public ViewGroup {
	ButtonViewItem fStartButton;

public:
	MainMenuViewGroup();
	explicit MainMenuViewGroup(const ViewAlignment& a);
};