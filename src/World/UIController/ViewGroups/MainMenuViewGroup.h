#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/ButtonViewItem.h"


class MainMenuViewGroup : public ViewGroup {
	ButtonViewItem fStartButton;

public:
	explicit MainMenuViewGroup(UIInterface& f);
	MainMenuViewGroup(UIInterface& f, const ViewAlignment& a);
};