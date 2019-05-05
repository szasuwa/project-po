#include "MapSelectionViewGroup.h"

MapSelectionViewGroup::MapSelectionViewGroup(UIInterface& f) : MapSelectionViewGroup(f, ViewAlignment::Left)
{
}

MapSelectionViewGroup::MapSelectionViewGroup(UIInterface& f, const ViewAlignment& a) : ViewGroup(f, a)
{
}