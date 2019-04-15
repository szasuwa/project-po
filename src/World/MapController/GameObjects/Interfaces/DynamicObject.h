#pragma once
#include <algorithm>

#include "../../../Frame/Frame.h"
#include "GameObject.h"
#include "Collider.h"


class DynamicObject : public GameObject
{
protected:
	float fMass;
	sf::Vector2f fForceVector;
	Collider fCollider;

	bool fVerticalInWindowLock;
	bool fHorizontalInWindowLock;

	void applyWorldForces();
	sf::Vector2f checkCollisions(const sf::Vector2f& p);
	sf::Vector2f lockInFrame(const sf::Vector2f & p);

public:
	explicit DynamicObject(Map * map = nullptr);
	DynamicObject(const sf::Vector2f & position, Map * map = nullptr);
	DynamicObject(bool vLock, bool hLock, Map * map = nullptr);
	DynamicObject(const sf::Vector2f & position, bool vLock, bool hLock, Map * map = nullptr);
	DynamicObject(const DynamicObject & o);
	~DynamicObject();

	virtual void move(const sf::Vector2f& p, bool gridSnap = false, bool vLock = false, bool hLock = false);
	void applyForces();

	virtual void serializeObject(std::ostream& ss) const;
	virtual void deserializeObject(std::istream& ss);
};

