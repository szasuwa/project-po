#pragma once
#include <sstream>
const int SERIALIZABLE_CLASS_TYPE_PLAYER = 1;
const int SERIALIZABLE_CLASS_TYPE_PLATFORM = 2;
const char SERIALIZABLE_OBJECT_DELIMITER = '\n';
const char SERIALIZABLE_FIELD_DELIMITER = ' ';

class Serializable
{
public:
	Serializable();
	~Serializable();

	virtual void serializeData(std::stringstream &ss, bool last = true);
	virtual void deserializeData(std::stringstream &ss) = 0;
};

