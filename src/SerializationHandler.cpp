#include "SerializationHandler.h"
#include <iostream>


SerializationHandler::SerializationHandler()
{
}


SerializationHandler::~SerializationHandler()
{
}

std::string SerializationHandler::serializeObject(Serializable * obj)
{
	std::stringstream ss;
	
	obj->serializeData(ss);
	
	std::cout << ss.str() << std::endl;

	return ss.str();
}

std::string SerializationHandler::serializeBundle(Serializable **obj, int size)
{
	std::stringstream ss;
	for (int i = 0; i < size; ++i) {
		if (i > 0)
			ss << SERIALIZABLE_OBJECT_DELIMITER;
		obj[i]->serializeData(ss);
	}
	
	return ss.str();
}

Serializable * SerializationHandler::deserializeObject(std::string &data, Level* lvl)
{
	std::stringstream ss;
	ss.str(data);
	int type;
	ss >> type;
	
	Serializable * output = nullptr;

	switch (type)
	{
		case SERIALIZABLE_CLASS_TYPE_PLAYER:
			output = new Player(lvl);
			break;

		case SERIALIZABLE_CLASS_TYPE_PLATFORM:
			output = new Platform(lvl);
			break;

		case SERIALIZABLE_CLASS_TYPE_POINT:
			output = new Point(lvl);
			break;

		default:
		return nullptr;
	}

	output->deserializeData(ss);
	if (lvl != nullptr) {
		lvl->addGameObject((GameObject*)output);
	}
	return output;
}

void SerializationHandler::deserializeBundle(std::string &data, Level* lvl)
{
	std::stringstream ss;
	ss.str(data);
	while (ss.rdbuf()->in_avail() > 0) {
		std::string temp;
		getline(ss, temp);
		deserializeObject(temp, lvl);
	}
}