#pragma once
#include <algorithm>

#include "../../../Frame/Frame.h"
#include "GameObject.h"
#include "Collider.h"


class PhysicalObject : public GameObject
{
protected:
	float fMass;
	sf::Vector2f fForceVector;
	Collider fCollider;

	bool fVerticalInWindowLock;
	bool fHorizontalInWindowLock;

	void applyWorldForces();
	void checkCollisions();
	virtual void checkCollision(const GameObject & obj);

public:
	explicit PhysicalObject(Map * map = nullptr);
	PhysicalObject(const sf::Vector2f & position, Map * map = nullptr);
	PhysicalObject(bool vLock, bool hLock, Map * map = nullptr);
	PhysicalObject(const sf::Vector2f & position, bool vLock, bool hLock, Map * map = nullptr);
	PhysicalObject(const PhysicalObject & o);
	~PhysicalObject();

	virtual void serializeObject(std::ostream & ss) const;
	virtual void deserializeObject(std::istream & ss);

	void applyForces();
};

