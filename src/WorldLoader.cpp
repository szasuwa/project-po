#include "WorldLoader.h"



WorldLoader::WorldLoader()
{
}


WorldLoader::~WorldLoader()
{
}

void WorldLoader::unloadLevel() {
	GameObject::destroyAll();
}

WorldBoundaries WorldLoader::loadLevel(int id) {
	WorldBoundaries out;

	std::ifstream fs(F_LEVEL_FILENAME + std::to_string(id));
	if (!fs.fail()) {
		std::stringstream bf;
		bf << fs.rdbuf();
		bf >> out.left;
		bf >> out.right;
		std::string temp = bf.str().erase(0, bf.str().find('\n') + 1);

		unloadLevel();
		fSerializationHandler.deserializeBundle(temp);
		
		fs.close();
	}

	return out;
}