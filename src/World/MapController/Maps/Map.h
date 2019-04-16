#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>
#include <vector>
#include <regex>

#include "MapBoundaries.h"
#include "../GameObjects/Interfaces/GameObject.h"
#include "../GameObjects/Interfaces/DynamicObject.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/Point.h"

class Map {
	MapBoundaries fMapBoundaries;
	std::vector<GameObject *> fGameObjectList;
	sf::FloatRect fCamera;

	float fDecelerationRate = 15.f;
	float fDecelerationSmoothRate = 0.1f;
	float fGravityRate = 15.f;
	float fMaxGravityForce = 500.f;

	friend DynamicObject;

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

	/*
		<<Data format>>
		Properties separated using SERIALIZABLE_FIELD_DELIMITER.
		Objects separated using SERIALIZABLE_OBJECT_DELIMITER.

		<<Data order>>
		map
		object[1]
		...
		object[n]

		<<Map properties order>>
		has left bound
		has right bound
		has top bound
		has bottom bound
		left bound
		right bound
		top bound
		bottom bound
		deceleration rate
		deceleration smooth rate
		gravity rate
		max gravity force
		camera left
		camera top
		camera width
		camera height
	*/

	void serializeObject(std::ostream& ss) const;
	void deserializeObject(std::istream& ss);
	static bool checkSerializableValidity(const std::string & s);
};

std::ostream& operator<<(std::ostream& s, const Map& o);
std::istream& operator>>(std::istream& s, Map& o);