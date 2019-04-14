#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>

#include "MapBoundaries.h"
#include "../GameObjects/Interfaces/GameObject.h"
#include "../GameObjects/Interfaces/PhysicalObject.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/Point.h"

class MapController;

class Map {
	MapBoundaries fMapBoundaries;
	std::vector<GameObject *> fGameObjectList;
	sf::FloatRect fCamera;

	float fDecelerationRate = 15.f;
	float fDecelerationSmoothRate = 0.1f;
	float fGravityRate = 15.f;
	float fMaxGravityForce = 500.f;

	friend PhysicalObject;
	friend MapController;

public:
	Map();
	Map(const Map & o);
	~Map();

	void addGameObject(GameObject* obj);
	void addGameObjects(const std::vector<GameObject *> &list);
	void destroyGameObject(GameObject* obj);
	void destroyAllGameObjects();
	
	const std::vector<GameObject *>& getGameObjects() const;

	MapBoundaries getBoundaries() const;
	void updateCamera();
	sf::FloatRect getCamera() const;
	void setCamera(const sf::FloatRect & camera);
	void moveCamera(const sf::Vector2f & p);
	
	void broadcastFocus();
	void broadcastUpdate();
	void broadcastDraw() const;

	void clone(const Map & o);
	Map & operator=(const Map & o);
};