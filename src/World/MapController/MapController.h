#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

#include "Maps/Map.h"
#include "GameObjects/Player.h"
#include "GameObjects/Platform.h"
#include "GameObjects/Point.h"
#include "Maps/MapEditor.h"
#include "../../Logger.h"


class MapController
{
private:
	static MapController * instance;
	const std::string F_MAP_PATH = "res/";
	std::vector<Map> fMapList = std::vector<Map>();
	Map * fActiveMap = nullptr;
	Map * fEditedMap = nullptr;
	std::string fActiveMapName;
	std::string fEditedMapName;
	int fActiveMapIndex;
	MapEditor * fEditor = nullptr;

	MapController();
	MapController(const MapController& o);

public:
	static MapController& getInstance();

	~MapController();

	bool load(const int & id);
	bool load(const std::string & name);
	bool load(const std::string& name, Map * map);
	void save(const std::string & name, const Map & map) const;
	bool exists(const std::string& name) const;
	bool checkIntegrity(const std::string& name) const;

	void beginEdition();
	void saveEditedMap();
	void resetEditedMap();
	void endEdition();
	void cancelEdition();

	void resetMap();

	void updateCamera();
	void updateMap();
	void updateEditor();
	void drawMap();
};

