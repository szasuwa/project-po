#include "MapSelectionViewGroup.h"
#include "../ViewActions/TextColorChangeViewAction.h"
#include "../ViewActions/MapSelectionViewAction.h"
#include "../ViewActions/SetBoolViewAction.h"
#include "../ViewActions/SetPointerViewAction.h"
#include "../ViewActions/GroupViewAction.h"
#include "../ViewActions/DeleteFileViewAction.h"


MapSelectionViewGroup::MapSelectionViewGroup(const ViewAlignment& a) : ViewGroup(a)
{
	fRefresh.setText("Refresh List");
	fRefresh.setOnClick(new SetBoolViewAction(fRefreshList, true));
	fRefresh.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fRefresh));
	fRefresh.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fRefresh));

	fLoadButton.setText("Load Map");
	fLoadButton.setColor(TEXT_INACTIVE_COLOR);

	fDeleteButton.setText("Delete Map");
	fDeleteButton.setColor(TEXT_INACTIVE_COLOR);
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
	fItemList.push_back(&fLoadButton);
	fItemList.push_back(&fSeparator);
	fItemList.push_back(&fDeleteButton);
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
			std::string fName = entry.path().filename().string();
			MapInfo info = f.getMapInterface().loadMapInfo(fName);

			if (!info.valid)
				continue;

			fMaps.push_back(new ButtonViewItem());
			ButtonViewItem* item = fMaps.back();
			item->setText(std::to_string(fMaps.size()) + ": " + info.name + " (" + fName + ")");
			item->setOnClick(
				new GroupViewAction
				(5,
					new SetPointerViewAction(
						fLoadAction,
						new GroupViewAction(
							3,
							new SetPointerViewAction(
								fLoadAction,
								nullptr
							),
							new SetPointerViewAction(
								fDeleteAction,
								nullptr
							),
							new MapSelectionViewAction(f, (unsigned int)InterfaceType::MapSelection, fName)
						)

					),
					new SetPointerViewAction(
						fDeleteAction,
						new GroupViewAction(
							6,
							new DeleteFileViewAction(entry.path().string()),
							new SetPointerViewAction(
								fLoadAction,
								nullptr
							),
							new SetPointerViewAction(
								fDeleteAction,
								nullptr
							),
							new SetPointerViewAction(
								fSelectedButton,
								nullptr
							),
							new SetBoolViewAction(fRefreshList, true),
							new SetBoolViewAction(fSelectionUpdate, true)
						)

					),
					new SetPointerViewAction(
						fSelectedButton,
						item
					),
				new SetBoolViewAction(fUpdateSelectedButton, true),
				new SetBoolViewAction(fSelectionUpdate, true)
			));
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

	if (fSelectionUpdate)
	{
		fSelectionUpdate = false;

		if (fPreviousSelectedButton != fSelectedButton)
		{
			if (fLoadAction != nullptr)
			{
				fLoadButton.setColor(TEXT_DEFAULT_COLOR);
				fLoadButton.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fLoadButton));
				fLoadButton.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fLoadButton));
				fLoadButton.setOnClick(reinterpret_cast<ViewAction*>(fLoadAction), true);
			}
			else
			{
				fLoadButton.setColor(TEXT_INACTIVE_COLOR);
				fLoadButton.setOnMouseEnter(nullptr);
				fLoadButton.setOnMouseExit(nullptr);
				fLoadButton.setOnClick(nullptr, true);
			}

			if (fDeleteAction != nullptr)
			{
				fDeleteButton.setColor(TEXT_DEFAULT_COLOR);
				fDeleteButton.setOnMouseEnter(new TextColorChangeViewAction(TEXT_ACTIVE_COLOR, fDeleteButton));
				fDeleteButton.setOnMouseExit(new TextColorChangeViewAction(TEXT_DEFAULT_COLOR, fDeleteButton));
				fDeleteButton.setOnClick(reinterpret_cast<ViewAction*>(fDeleteAction), true);
			}
			else
			{
				fDeleteButton.setColor(TEXT_INACTIVE_COLOR);
				fDeleteButton.setOnMouseEnter(nullptr);
				fDeleteButton.setOnMouseExit(nullptr);
				fDeleteButton.setOnClick(nullptr, true);
			}
		}

		fPreviousSelectedButton = fSelectedButton;
	}

	if (fUpdateSelectedButton)
	{
		for (ButtonViewItem* item : fMaps)
		{
			if (item != fSelectedButton)
			{
				item->setColor(TEXT_DEFAULT_COLOR);
			}
			else
			{
				item->setColor(TEXT_SELECTED_COLOR);
			}
		}
	}

	ViewGroup::update(f);
}
