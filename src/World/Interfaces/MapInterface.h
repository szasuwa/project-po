#pragma once
#include "GameEngineInterface.h"
#include <string>

class Map;

class MapInterface
{
protected:
	GameEngineInterface * fEngine = nullptr;

public:
	virtual ~MapInterface() {};

	GameEngineInterface& getEngine() { return *fEngine; }
	void setEngine(GameEngineInterface & engine) { fEngine = &engine; }

	virtual bool load(const int & id) = 0;
	virtual bool load(const std::string & name) = 0;
	virtual bool load(const std::string& name, Map * map) = 0;
	virtual void save(const std::string & name, const Map & map) const = 0;
	virtual bool exists(const std::string& name) const = 0;
	virtual bool checkIntegrity(const std::string& name) const = 0;

	virtual void beginEdition() = 0;
	virtual void saveEditedMap() = 0;
	virtual void resetEditedMap() = 0;
	virtual void endEdition() = 0;
	virtual void cancelEdition() = 0;

	virtual void resetMap() = 0;
	virtual void unloadMap() = 0;

	virtual void updateCamera() = 0;
	virtual void updateMap() = 0;
	virtual void updateEditor() = 0;
	virtual void drawMap() = 0;
};

