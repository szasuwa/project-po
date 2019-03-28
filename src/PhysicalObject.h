#pragma once
#include "GameObject.h"
#include "Frame.h"
#include "Collider.h"
#include <algorithm>

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
	PhysicalObject(Level* lvl = nullptr);
	PhysicalObject(bool boundsV, bool boundsH, Level* lvl = nullptr);
	~PhysicalObject();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	void handleForces();
};

