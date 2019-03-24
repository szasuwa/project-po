#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "SerializationHandler.h"
#include "Platform.h"

class GameObject;
class Player;

class World
{
	const std::string F_LEVEL_FILENAME = "res/level";
	static sf::Vector2f fOrigin;

	static float fWorldBoundaryLeft;
	static float fWorldBoundaryRight;

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

	//Map movement
	static void scrollMap(float v);
	static float getWorldBoundaryLeft();
	static float getWorldBoundaryRight();
};

