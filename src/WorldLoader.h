#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "SerializationHandler.h"
#include "WorldBoundaries.h"

class WorldLoader
{
	const std::string F_LEVEL_FILENAME = "res/level";

	SerializationHandler fSerializationHandler;

public:
	WorldLoader();
	~WorldLoader();

	void unloadLevel();
	WorldBoundaries loadLevel(int id);
};

