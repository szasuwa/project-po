#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

#include "../Interfaces/MapInterface.h"
#include "Maps/Map.h"
#include "Maps/MapEditor.h"
#include "../../Logger.h"
#include "../../Libs/base64.h"


class MapController : public MapInterface
{
private:
	const std::string F_MAP_PATH = "res/maps/";
	std::vector<Map> fMapList = std::vector<Map>();
	Map * fActiveMap = nullptr;
	Map * fEditedMap = nullptr;
	std::string fActiveMapName;
	std::string fEditedMapName;
	int fActiveMapIndex;
	MapEditor * fEditor = nullptr;

public:
	using MapInterface::MapInterface;
	~MapController();

	virtual bool load(const int & id);
	virtual bool load(const std::string & name);
	virtual bool load(const std::string& name, Map * map);
	virtual void save(const std::string & name, const Map & map) const;
	virtual bool exists(const std::string& name) const;
	virtual bool checkIntegrity(const std::string& name) const;
	virtual MapInfo loadMapInfo(const std::string& name) const;

	virtual void beginEdition();
	virtual void saveEditedMap();
	virtual void resetEditedMap();
	virtual void endEdition();
	virtual void cancelEdition();

	virtual void resetMap();
	virtual void unloadMap();

	virtual void updateCamera();
	virtual void updateMap();
	virtual void updateEditor();
	virtual void drawMap();
};

