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


class MapController
{
	const std::string F_MAP_PATH = "res/";
	std::vector<Map> fMapList;
	Map * fActiveMap = nullptr;
	Map * fEditedMap = nullptr;
	std::string fActiveMapName;
	std::string fEditedMapName;
	int fActiveMapIndex;
	MapEditor * fEditor = nullptr;

public:
	void load(const int & id);
	void load(const std::string & name);
	void load(const std::string& name, Map * map);
	void save(const std::string & name, const Map & map) const;
	bool exists(const std::string& name) const;

	/*
		<<Data format>>
		Properties separated using SERIALIZABLE_FIELD_DELIMITER.
		Objects separated using SERIALIZABLE_OBJECT_DELIMITER.

		<<Data order>>
		map
		object[1]
		...
		object[n]

		<<Map properties order>>
		has left bound
		has right bound
		has top bound
		has bottom bound
		left bound
		right bound
		top bound
		bottom bound
		deceleration rate
		deceleration smooth rate
		gravity rate
		max gravity force
		camera left
		camera top
		camera width
		camera height
	*/
	std::string serializeMap(const Map & map) const;
	GameObject * deserializeGameObject(const std::string s);
	void deserializeMap(const std::string & s, Map * map);

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

