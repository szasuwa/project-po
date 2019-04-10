#include "MapManager.h"

MapManager::MapManager()
{
}

Map* MapManager::load(int id) {
	std::ifstream fs(F_MAP_PATH + std::to_string(id));

	if (fs.fail())
		return nullptr;

	fMapList.push_back(Map());
	Map* map = &fMapList.back();

	std::stringstream bf;
	bf << fs.rdbuf();

	float l, r;
	bf >> l;
	bf >> r;
	map->setMapBoundaries(l, r);

	std::string temp = bf.str().erase(0, bf.str().find('\n') + 1);
	std::vector<Serializable*> vs = fSerializationHandler.deserializeBundle(temp);
	std::vector<GameObject*> vg;
	for (Serializable* s : vs) {
		vg.push_back((GameObject*)s);
	}
	map->addGameObjects(vg);

	fs.close();

	return map;
}