#pragma once 
#include <vector>

#include "../Interfaces/ViewGroup.h"
#include "../ViewItems/ButtonViewItem.h"


class MapSelectionViewGroup : public ViewGroup {
	std::vector<ButtonViewItem> fMaps;

public:
	explicit MapSelectionViewGroup(const ViewAlignment& a);
};