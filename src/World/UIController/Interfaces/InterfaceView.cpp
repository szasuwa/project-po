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

void InterfaceView::setProperty(const unsigned int& i, const std::string& v)
{
	if (i >= fPropertyList.size())
		throw std::out_of_range("Property does not exist (Size: " + std::to_string(fPropertyList.size()) + " , requested: " + std::to_string(i) + ")");

	fPropertyList[i] = v;
}

std::string InterfaceView::getProperty(const unsigned int& i)
{
	if (i >= fPropertyList.size())
		throw std::out_of_range("Property does not exist (Size: " + std::to_string(fPropertyList.size()) + " , requested: " + std::to_string(i) + ")");

	return fPropertyList[i];
}