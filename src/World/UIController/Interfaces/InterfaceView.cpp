#include "InterfaceView.h"

void InterfaceView::updateView(UIInterface& f)
{
}

void InterfaceView::update(UIInterface& f)
{
	for (ViewGroup* item : fGroupList)
	{
		if (item != nullptr)
		{
			item->update(f);
		}
	}
}

void InterfaceView::draw(UIInterface& f)
{
	if (!fVisible)
		return;

	for (ViewGroup* item : fGroupList)
	{
		if (item != nullptr)
		{
			item->calculatePositions();
			item->draw(f);
		}
	}
}