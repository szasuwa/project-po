#pragma once
#include "Serializable.h"
#include "Player.h"
#include "Platform.h"
#include <sstream>
#include <string>



class SerializationHandler
{

public:
	SerializationHandler();
	~SerializationHandler();
	std::string serializeObject(Serializable *obj);
	std::string serializeBundle(Serializable **obj, int size);
	Serializable * deserializeObject(std::string &data);
	std::vector<Serializable *> * deserializeBundle(std::string &data);
};

