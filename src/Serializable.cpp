#include "Serializable.h"



Serializable::Serializable()
{
}


Serializable::~Serializable()
{
}

void Serializable::serializeData(std::stringstream &ss, bool last) {
	if (!last) {
		ss << SERIALIZABLE_FIELD_DELIMITER;
	}
}