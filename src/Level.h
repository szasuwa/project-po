#pragma once
#include "GameObject.h"
#include "WorldBoundaries.h"
#include "Frame.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

class Level {
	WorldBoundaries fWorldBoundaries;
	std::vector<GameObject *> fGameObjectList;
	sf::Vector2f fLevelOrigin;

public:
	Level();
	~Level();

	void addGameObject(GameObject* obj);
	void destroyGameObject(GameObject* obj);
	void destroyAllGameObjects();
	const std::vector<GameObject *>& getGameObjectList() const;

	void setWorldBoundaries(float l, float r);
	void scrollMap(float x);
	
	void broadcastOriginChange(const sf::Vector2f &o);
	void broadcastUpdate();
	void broadcastDraw(sf::RenderWindow &w);
};