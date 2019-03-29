#pragma once
#include <sstream>
#include <string>

#include "../Levels/Level.h"
#include "Serializable.h"
#include "../Objects/Actors/Player.h"
#include "../Objects/Map/Platform.h"
#include "../Objects/Map/Point.h"


class SerializationHandler
{

public:
	SerializationHandler();
	~SerializationHandler();
	std::string serializeObject(Serializable *obj);
	std::string serializeBundle(Serializable **obj, int size);
	Serializable * deserializeObject(std::string &data, Level* lvl = nullptr);
	void deserializeBundle(std::string &data, Level* lvl = nullptr);
};

