#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
	MapEditor * fEditor = nullptr;

public:
	Map * load(const int & id);
	Map * load(const std::string & name);
	void save(const std::string & name, const Map & map) const;

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
	*/
	std::string serializeMap(const Map & map) const;
	GameObject * deserializeGameObject(const std::string s);
	void deserializeMap(const std::string & s, Map * map);

	void startEditing();
	void saveEditedMap();
	void resetEditedMap();
	void stopEditing();
	void cancelEditing();

	void updateCamera();
	void updateMap();
	void updateEditor();
	void drawMap();
};

