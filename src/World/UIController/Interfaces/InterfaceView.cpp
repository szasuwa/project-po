#include "InterfaceView.h"

void InterfaceView::updateView(GameEngineInterface& f)
{
}

void InterfaceView::update(GameEngineInterface& f)
{
	for (ViewGroup* item : fGroupList)
	{
		if (item != nullptr)
		{
			item->update(f);
		}
	}
}

void InterfaceView::draw(GameEngineInterface& f)
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

void InterfaceView::setProperty(const unsigned int& id, const std::string& v)
{
	if (id >= fPropertyList.size())
		throw std::out_of_range("Property does not exist (Size: " + std::to_string(fPropertyList.size()) + " , requested: " + std::to_string(id) + ")");

	fPropertyList[id] = v;
}

std::string InterfaceView::getProperty(const unsigned int& id)
{
	if (id >= fPropertyList.size())
		throw std::out_of_range("Property does not exist (Size: " + std::to_string(fPropertyList.size()) + " , requested: " + std::to_string(id) + ")");

	return fPropertyList[id];
}