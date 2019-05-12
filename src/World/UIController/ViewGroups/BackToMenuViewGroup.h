#pragma once 
#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/ButtonViewItem.h"
#include "../InterfaceType.h"


class BackToMenuViewGroup : public ViewGroup {
	ButtonViewItem fBackToMenu;

public:
	BackToMenuViewGroup(GameEngineInterface& f);
	BackToMenuViewGroup(GameEngineInterface& f, const ViewAlignment& a);
};