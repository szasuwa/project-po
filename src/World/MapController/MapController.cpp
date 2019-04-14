#include "MapController.h"
#include <iostream>

void MapController::load(const int & id) {
	if (fMapList.size() >= id)
		return;
	
	fActiveMap = &fMapList[id];
	fActiveMapIndex = id;
	fActiveMap->broadcastFocus();
}

void MapController::load(const std::string & name)
{
	if (!exists(name))
		return;

	fMapList.push_back(Map());
	fActiveMap = &fMapList.back();
	fActiveMapName = name;
	fActiveMapIndex = fMapList.size() - 1;

	load(name, fActiveMap);

	fActiveMap->broadcastFocus();
}

void MapController::load(const std::string& name, Map * map)
{
	std::ifstream fs(F_MAP_PATH + name);

	if (fs.fail())
		return;

	std::stringstream bf;
	bf << fs.rdbuf();
	deserializeMap(bf.str(), map);

	fs.close();
}

void MapController::save(const std::string & name, const Map & map) const
{
	std::ofstream fs(F_MAP_PATH + name);

	if (fs.fail())
		return;

	fs << serializeMap(map);

	fs.close();
}

bool MapController::exists(const std::string& name) const
{
	std::ifstream f(F_MAP_PATH + name);
	return f.good();
}

std::string MapController::serializeMap(const Map & map) const
{
	std::stringstream ss;

	ss << map.fMapBoundaries.hasLeft << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.hasRight << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.hasTop << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.hasBottom << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.left << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.right << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.top << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMapBoundaries.bottom << SERIALIZABLE_FIELD_DELIMITER
		<< map.fDecelerationRate << SERIALIZABLE_FIELD_DELIMITER
		<< map.fDecelerationSmoothRate << SERIALIZABLE_FIELD_DELIMITER
		<< map.fGravityRate << SERIALIZABLE_FIELD_DELIMITER
		<< map.fMaxGravityForce << SERIALIZABLE_FIELD_DELIMITER
		<< map.fCamera.left << SERIALIZABLE_FIELD_DELIMITER
		<< map.fCamera.top << SERIALIZABLE_FIELD_DELIMITER
		<< map.fCamera.width << SERIALIZABLE_FIELD_DELIMITER
		<< map.fCamera.height << SERIALIZABLE_FIELD_DELIMITER;

	for (GameObject * obj : map.fGameObjectList)
	{
		if (obj != nullptr)
			ss << SERIALIZABLE_OBJECT_DELIMITER << *obj ;
	}

	return ss.str();
}

GameObject * MapController::deserializeGameObject(const std::string s) 
{
	std::stringstream ss;
	ss.str(s);
	int type;
	ss >> type;

	GameObject * output = nullptr;

	switch ((GameObjectClassType)type)
	{
	case GameObjectClassType::PLAYER:
		output = new Player();
		break;

	case GameObjectClassType::PLATFORM:
		output = new Platform();
		break;

	case GameObjectClassType::POINT:
		output = new Point();
		break;

	default:
		return nullptr;
	}

	ss >> *output;
	return output;
}

void MapController::deserializeMap(const std::string & s, Map * map)
{
	std::stringstream ss;
	ss.str(s);

	ss >> (*map).fMapBoundaries.hasLeft >> (*map).fMapBoundaries.hasRight >> (*map).fMapBoundaries.hasTop >> (*map).fMapBoundaries.hasBottom >> 
		(*map).fMapBoundaries.left >> (*map).fMapBoundaries.right >> (*map).fMapBoundaries.top >> (*map).fMapBoundaries.bottom >>
		(*map).fCamera.left >> (*map).fCamera.top >> (*map).fCamera.width >> (*map).fCamera.height;

	ss.ignore(255, SERIALIZABLE_OBJECT_DELIMITER);

	map->destroyAllGameObjects();

	while (ss.rdbuf()->in_avail() > 0) {
		std::string temp;
		getline(ss, temp);
		map->addGameObject(deserializeGameObject(temp));
	}
}

void MapController::beginEdition()
{
	fEditedMap = fActiveMap;
	fEditedMapName = fActiveMapName;

	fEditor = new MapEditor();
	time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	fActiveMapName = fEditedMapName + "_" + std::to_string(t);
	fActiveMap = fEditor->loadMap(*fEditedMap);
	fActiveMap->broadcastFocus();
}

void MapController::saveEditedMap()
{
	if (fEditor == nullptr)
		return;

	save(fActiveMapName, *fActiveMap);
}

void MapController::resetEditedMap() 
{
	if (fEditor == nullptr)
		return;

	if (exists(fActiveMapName))
		load(fActiveMapName, fActiveMap);
	else
		fActiveMap = fEditedMap;

	fActiveMap = fEditor->loadMap(*fActiveMap);
	fActiveMap->broadcastFocus();
}

void MapController::endEdition()
{
	if (fEditor == nullptr)
		return;

	fMapList[fActiveMapIndex].clone(*fActiveMap);
	fActiveMap = &fMapList[fActiveMapIndex];
	fActiveMap->broadcastFocus();
	fActiveMapName = fEditedMapName;
	save(fActiveMapName, *fActiveMap);

	fEditedMap = nullptr;
	delete fEditor;
	fEditor = nullptr;
}

void MapController::cancelEdition()
{
	if (fEditor == nullptr)
		return;

	fActiveMapName = fEditedMapName;
	fActiveMap = fEditedMap;
	fActiveMap->broadcastFocus();

	fEditedMap = nullptr;
	delete fEditor;
	fEditor = nullptr;
}

void MapController::resetMap() 
{
	if (fActiveMap == nullptr)
		return;

	load(fActiveMapName, fActiveMap);
	fActiveMap->broadcastFocus();
}

void MapController::updateCamera()
{
	if (fActiveMap == nullptr)
		return;

	fActiveMap->updateCamera();
}

void MapController::updateMap()
{
	if (fActiveMap == nullptr)
		return;

	fActiveMap->broadcastUpdate();
}

void MapController::updateEditor()
{
	if (fActiveMap == nullptr || fEditor == nullptr)
		return;

	fEditor->update();
}

void MapController::drawMap()
{
	if (fActiveMap == nullptr)
		return;
	
	fActiveMap->broadcastDraw();
}
