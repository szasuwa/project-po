#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "SerializationHandler.h"
#include "WorldBoundaries.h"
#include "Level.h"

class LevelLoader
{
	const std::string F_LEVEL_FILENAME = "res/level";

	SerializationHandler fSerializationHandler;

public:
	LevelLoader();

	Level* loadLevel(int id);
};

