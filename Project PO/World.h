#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "SerializationHandler.h"
#include "Platform.h"

class GameObject;
class Player;

static class World
{
	const std::string F_LEVEL_FILENAME = "level";

	static int fNextGameObjectId;
	static std::vector<GameObject*> fGameObjects;
	static Player* fPlayerObject;

	SerializationHandler fSerializationHandler;

	void unloadLevel();
public:
	World();
	~World();

	//Levels
	void loadLevel(int id);

	//GameObjects
	static void setPlayer(Player *player);
	static int getNextGameObjectId();
	static const std::vector<GameObject*> getGameObjectList();
	static GameObject* findGameObject(int id);
	static void destroyGameObjects();
	static void addGameObject(GameObject* object);
};

