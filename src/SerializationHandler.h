#pragma once
#include "Level.h"
#include "Serializable.h"
#include "Player.h"
#include "Platform.h"
#include "Point.h"
#include <sstream>
#include <string>



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

