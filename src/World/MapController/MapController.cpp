#include "MapController.h"
#include <iostream>

Map* MapController::load(const int & id) {
	if (fMapList.size() >= id)
		return nullptr;
	
	fActiveMap = &fMapList[id];
	fActiveMapIndex = id;
	fActiveMap->updateCamera();

	return fActiveMap;
}

Map * MapController::load(const std::string & name)
{
	std::ifstream fs(F_MAP_PATH + name);

	if (fs.fail())
		return nullptr;

	fMapList.push_back(Map());
	fActiveMap = &fMapList.back();
	fActiveMapName = name;
	fActiveMapIndex = fMapList.size() - 1;

	std::stringstream bf;
	bf << fs.rdbuf();
	deserializeMap(bf.str(), fActiveMap);
	fs.close();

	fActiveMap->updateCamera();

	return fActiveMap;
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
		<< map.fMaxGravityForce;

	for (GameObject * obj : map.fGameObjectList)
	{
		if (obj != nullptr)
			ss << SERIALIZABLE_OBJECT_DELIMITER << *obj;
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
		(*map).fMapBoundaries.left >> (*map).fMapBoundaries.right >> (*map).fMapBoundaries.top >> (*map).fMapBoundaries.bottom;
	
	ss.ignore(255, SERIALIZABLE_OBJECT_DELIMITER);

	while (ss.rdbuf()->in_avail() > 0) {
		std::string temp;
		getline(ss, temp);
		map->addGameObject(deserializeGameObject(temp));
	}
}

void MapController::startEditing()
{
	fEditedMap = fActiveMap;
	fEditedMapName = fActiveMapName;

	fEditor = new MapEditor();
	time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	fActiveMapName = fEditedMapName + "_" + std::to_string(t);
	fActiveMap = fEditor->loadMap(*fEditedMap);
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
		fActiveMap = load(fActiveMapName);
	else
	{
		fActiveMap = fEditedMap;
	}

	fActiveMap = fEditor->loadMap(*fActiveMap);
}

void MapController::stopEditing()
{
	if (fEditor == nullptr)
		return;

	fMapList[fActiveMapIndex].clone(*fActiveMap);
	fActiveMap = &fMapList[fActiveMapIndex];
	save(fEditedMapName, *fActiveMap);

	fEditedMap = nullptr;
	delete fEditor;
	fEditor = nullptr;
}

void MapController::cancelEditing()
{
	if (fEditor == nullptr)
		return;

	fActiveMap = fEditedMap;
	fEditedMap = nullptr;
	delete fEditor;
	fEditor = nullptr;
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
