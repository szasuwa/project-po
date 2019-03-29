#include "LevelLoader.h"

LevelLoader::LevelLoader()
{
}

Level* LevelLoader::loadLevel(int id) {
	std::ifstream fs(F_LEVEL_FILENAME + std::to_string(id));

	if (fs.fail())
		return nullptr;

	Level* lvl = new Level();

	std::stringstream bf;
	bf << fs.rdbuf();

	float l, r;
	bf >> l;
	bf >> r;
	lvl->setWorldBoundaries(l, r);

	std::string temp = bf.str().erase(0, bf.str().find('\n') + 1);
	fSerializationHandler.deserializeBundle(temp, lvl);

	fs.close();

	return lvl;
}