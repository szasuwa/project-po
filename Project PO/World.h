#pragma once
#include <vector>

class GameObject;
class Player;

static class World
{
	static int fNextGameObjectId;
	static std::vector<GameObject*> fGameObjects;
	static Player* fPlayerObject;

	void unloadLevel();
public:
	World();
	~World();

	//Levels
	void loadDevLevel();

	//void loadLevel(int id);

	//Update
	void callUpdate();
	//void callFixedUpdate();

	//GameObjects
	static int getNextGameObjectId();
	static const std::vector<GameObject*> const getGameObjectList();
	static GameObject* findGameObject(int id);
	static void addGameObject(GameObject* object);
	static void destroyGameObject(GameObject* object);
	static void destroyGameObject(int id);
};

