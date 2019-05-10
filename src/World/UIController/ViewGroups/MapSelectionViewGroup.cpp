#include "MapSelectionViewGroup.h"
#include "../ViewActions/TextColorChangeViewAction.h"
#include "../ViewActions/MapSelectionViewAction.h"
#include "../ViewActions/SetBoolViewAction.h"


MapSelectionViewGroup::MapSelectionViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fRefresh.setText("Refresh List");
	fRefresh.setOnClick(new SetBoolViewAction(fRefreshList, true));
	fRefresh.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fRefresh));
	fRefresh.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fRefresh));
}

MapSelectionViewGroup::~MapSelectionViewGroup()
{
	for (ButtonViewItem* item : fMaps)
	{
		delete item;
	}
}

void MapSelectionViewGroup::refreshList(GameEngineInterface& f)
{
	fItemList.clear();

	fItemList.push_back(&fRefresh);
	fItemList.push_back(&fSeparator);
	
	for (ButtonViewItem* item : fMaps)
	{
		delete item;
	}
	fMaps.clear();

	std::filesystem::path p(F_MAP_PATH);
	for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(p))
	{
		if (!entry.is_directory())
		{
			fMaps.push_back(new ButtonViewItem());
			ButtonViewItem* item = fMaps.back();
			item->setText(entry.path().filename().string());
			item->setOnClick(new MapSelectionViewAction(f, (unsigned int)InterfaceType::MapSelection, entry.path().filename().string()));
			item->setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, *item));
			item->setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, *item));
			fItemList.push_back(item);
		}
	}
}

void MapSelectionViewGroup::update(GameEngineInterface& f)
{
	if (fRefreshList)
	{
		fRefreshList = false;
		refreshList(f);
	}

	ViewGroup::update(f);
}
