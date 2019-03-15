#include "GameEngineConstants.h"
int GameEngineConstants::fNextGameObjectId;

int GameEngineConstants::getNextGameObjectId() {
	++fNextGameObjectId;
	return fNextGameObjectId;
}