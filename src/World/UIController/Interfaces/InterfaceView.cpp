#include "InterfaceView.h"

void InterfaceView::updateView()
{
}

void InterfaceView::update()
{
	for (ViewGroup* item : fGroupList)
	{
		if (item != nullptr)
		{
			item->update();
		}
	}
}

void InterfaceView::draw()
{
	if (!fVisible)
		return;

	for (ViewGroup* item : fGroupList)
	{
		if (item != nullptr)
		{
			item->calculatePositions();
			item->draw();
		}
	}
}