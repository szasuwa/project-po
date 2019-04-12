#pragma once
#include <sstream>

const char SERIALIZABLE_OBJECT_DELIMITER = '\n';
const char SERIALIZABLE_FIELD_DELIMITER = ' ';


class Serializable
{
public:
	enum CLASS_TYPE {
		NONE = 0,
		PLAYER = 1,
		PLATFORM = 2,
		POINT = 3
	};

	Serializable();

	virtual void serializeData(std::stringstream &ss, bool last = true);
	virtual void deserializeData(std::stringstream &ss) = 0;
	virtual CLASS_TYPE getClassType() = 0;
};

