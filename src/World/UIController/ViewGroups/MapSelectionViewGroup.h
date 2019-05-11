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
	ButtonViewItem fLoadButton;
	ButtonViewItem fDeleteButton;

	void* fPreviousSelectedButton = nullptr;
	void* fSelectedButton = nullptr;

	bool fRefreshList = true;
	bool fSelectionUpdate = true;
	bool fUpdateSelectedButton = false;
	void* fLoadAction = nullptr;
	void* fDeleteAction = nullptr;

	void refreshList(GameEngineInterface& f);

public:
	explicit MapSelectionViewGroup(const ViewAlignment& a);
	virtual ~MapSelectionViewGroup();
	virtual void update(GameEngineInterface& f);
};