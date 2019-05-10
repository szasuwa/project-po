#pragma once 
#include <vector>
#include <filesystem>

#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/ButtonViewItem.h"
#include "../ViewItems/SeparatorViewItem.h"
#include "../../MapController/MapController.h"
#include "../../../GameConstants.h"


class MapSelectionViewGroup : public ViewGroup {
	const std::string F_MAP_PATH = "res/maps/";
	ButtonViewItem fRefresh;
	SeparatorViewItem fSeparator;
	std::vector<ButtonViewItem*> fMaps;

	bool fRefreshList = true;

	void refreshList(GameEngineInterface& f);

public:
	explicit MapSelectionViewGroup(const ViewAlignment& a);
	virtual ~MapSelectionViewGroup();
	virtual void update(GameEngineInterface& f);
};