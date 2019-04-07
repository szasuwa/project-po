#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

#include "../Objects/Bases/GameObject.h"
#include "WorldBoundaries.h"
#include "../Frame.h"
#include "MapGrid.h"


class Level {
	WorldBoundaries fWorldBoundaries;
	std::vector<GameObject *> fGameObjectList;
	sf::Vector2f fLevelOrigin;
	MapGrid * fGrid;

public:
	Level();
	~Level();

	void addGameObject(GameObject* obj);
	void destroyGameObject(GameObject* obj);
	void destroyAllGameObjects();
	const std::vector<GameObject *>& getGameObjectList() const;

	void setGrid(MapGrid* grid);
	void setWorldBoundaries(float l, float r);
	void scrollMap(float x);
	
	void broadcastOriginChange(const sf::Vector2f &o);
	void broadcastUpdate();
	void broadcastDraw(sf::RenderWindow &w);
};