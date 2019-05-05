#include "MapController.h"


MapController::~MapController() 
{
	delete fEditor;
}

bool MapController::load(const int & id) {
	if (fMapList.size() >= id)
		return false;
	
	fActiveMap = &fMapList[id];
	fActiveMapIndex = id;
	fActiveMap->broadcastFocus();

	return true;
}

bool MapController::load(const std::string & name)
{
	if (!exists(name))
	{
		LogError("Cannot open file (" + F_MAP_PATH + name + ")");
		return false;
	}

	if (!checkIntegrity(name))
		return false;

	fMapList.push_back(Map(*this));
	fActiveMap = &fMapList.back();
	fActiveMapName = name;
	fActiveMapIndex = fMapList.size() - 1;

	load(name, fActiveMap);

	fActiveMap->broadcastFocus();

	return true;
}

bool MapController::load(const std::string& name, Map * map)
{
	std::ifstream fs(F_MAP_PATH + name);

	if (fs.fail())
	{
		LogError("Cannot open file (" + F_MAP_PATH + name + ")");
		return false;
	}

	if (!checkIntegrity(name))
		return false;

	fs >> *map;

	return true;
}

void MapController::save(const std::string & name, const Map & map) const
{
	std::ofstream fs(F_MAP_PATH + name);

	if (fs.fail())
	{
		LogError("Cannot open file (" + F_MAP_PATH + name + ")");
		return;
	}

	fs << map;
}

bool MapController::exists(const std::string& name) const
{
	std::ifstream f(F_MAP_PATH + name);
	return f.good();
}

bool MapController::checkIntegrity(const std::string& name) const
{
	std::ifstream fs(F_MAP_PATH + name);

	if (fs.fail())
	{
		LogError("Cannot open file (" + F_MAP_PATH + name + ")");
		return false;
	}

	std::string temp;
	int lines = 1;

	getline(fs, temp);
	if (!Map::checkSerializableValidity(temp))
	{
		LogError("Corrupted map (" + F_MAP_PATH + name + ") : " + std::to_string(lines));
		return false;
	}

	
	while (fs.rdbuf()->in_avail() > 0) {
		++lines;
		bool valid;
		int type;
		fs >> type;

		getline(fs, temp);

		switch ((GameObjectClassType)type)
		{
		case GameObjectClassType::PLAYER:
			valid = Player::checkSerializableValidity(temp);
			break;

		case GameObjectClassType::PLATFORM:
			valid = Platform::checkSerializableValidity(temp);
			break;

		case GameObjectClassType::POINT:
			valid = Point::checkSerializableValidity(temp);
			break;

		case GameObjectClassType::PORTAL:
			valid = Portal::checkSerializableValidity(temp);
			break;

		case GameObjectClassType::BOX:
			valid = Box::checkSerializableValidity(temp);
			break;

		default:
			valid = false;
		}

		if (!valid)
		{
			LogError("Corrupted object (" + F_MAP_PATH + name + ") : " + std::to_string(lines));
			return false;
		}
	}

	return true;
}

void MapController::beginEdition()
{
	fEditedMap = fActiveMap;
	fEditedMapName = fActiveMapName;

	fEditor = new MapEditor(*this);
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

	if (fEditor != nullptr)
		fEditor->draw();
}
