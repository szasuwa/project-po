#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/ButtonViewItem.h"


class MainMenuViewGroup : public ViewGroup {
	ButtonViewItem fStartButton;

public:
	explicit MainMenuViewGroup(GameEngineInterface& f);
	MainMenuViewGroup(GameEngineInterface& f, const ViewAlignment& a);
};