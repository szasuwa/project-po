#pragma once
#include <string>
#include <vector>
#include <fstream>

#include "../../Serialization/SerializationHandler.h"
#include "../Bases/MapBoundaries.h"
#include "../Bases/Map.h"


class MapManager
{
	const std::string F_MAP_PATH = "res/map";
	std::vector<Map> fMapList;

	SerializationHandler fSerializationHandler;

public:
	MapManager();

	Map* load(int id);
};

