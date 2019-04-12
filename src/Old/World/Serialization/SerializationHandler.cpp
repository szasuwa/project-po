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

Serializable * SerializationHandler::deserializeObject(std::string &data)
{
	std::stringstream ss;
	ss.str(data);
	int type;
	ss >> type;
	
	Serializable * output = nullptr;

	switch (type)
	{
		case Serializable::CLASS_TYPE::PLAYER:
			output = new Player();
			break;

		case Serializable::CLASS_TYPE::PLATFORM:
			output = new Platform();
			break;

		case Serializable::CLASS_TYPE::POINT:
			output = new Point();
			break;

		default:
		return nullptr;
	}

	output->deserializeData(ss);
	return output;
}

std::vector<Serializable*> SerializationHandler::deserializeBundle(std::string &data)
{
	std::vector<Serializable*> output;
	std::stringstream ss;
	ss.str(data);
	while (ss.rdbuf()->in_avail() > 0) {
		std::string temp;
		getline(ss, temp);
		output.push_back(deserializeObject(temp));
	}
	return output;
}