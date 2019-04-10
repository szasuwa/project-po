#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "../../Objects/Bases/GameObject.h"
#include "MapBoundaries.h"
#include "../../Frame.h"
#include "../Editor/MapGrid.h"


class Map {
	MapBoundaries fWorldBoundaries;
	std::vector<GameObject *> fGameObjectList;
	sf::Vector2f fMapOrigin;
	MapGrid * fGrid;

public:
	Map();
	~Map();

	void addGameObject(GameObject* obj);
	void addGameObjects(const std::vector<GameObject *> &list);
	void destroyGameObject(GameObject* obj);
	void destroyAllGameObjects();
	
	const std::vector<GameObject *>& getGameObjectList() const;

	void setGrid(MapGrid* grid);
	void setMapBoundaries(float l, float r);
	void scrollMap(float x);
	
	void broadcastOriginChange(const sf::Vector2f &o);
	void broadcastUpdate();
	void broadcastDraw(sf::RenderWindow &w);
};