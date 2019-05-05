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
	for (ViewGroup* item : fGroupList)
	{
		if (item != nullptr)
		{
			item->calculatePositions();
			item->draw();
		}
	}
}