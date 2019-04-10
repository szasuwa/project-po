#pragma once
#include <sstream>
#include <string>
#include <vector>

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
	Serializable * deserializeObject(std::string &data);
	std::vector<Serializable*> deserializeBundle(std::string &data);
};

