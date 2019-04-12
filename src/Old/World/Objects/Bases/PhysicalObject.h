#pragma once
#include <algorithm>

#include "../../Frame.h"
#include "GameObject.h"
#include "Collider.h"


class PhysicalObject : public GameObject
{
protected:
	static float fDecelerationRate;
	static float fDecelerationSmoothRate;
	static float fGravityRate;
	static float fGravityForce;
	sf::Vector2f fForceVector;

	Collider fCollider;

	bool fInWindowBoundsVertical;
	bool fInWindowBoundsHorizontal;

	void applyDeceleration();
	void applyGravity();
	void handleCollisions();
	virtual void checkCollision(GameObject* obj);

public:
	explicit PhysicalObject(Map* map = nullptr);
	PhysicalObject(const sf::Vector2f &position, Map* map = nullptr);
	PhysicalObject(bool boundsV, bool boundsH, Map* map = nullptr);
	PhysicalObject(const sf::Vector2f &position, bool boundsV, bool boundsH, Map* map = nullptr);
	PhysicalObject(const PhysicalObject &obj);
	~PhysicalObject();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	void handleForces();
};

