#pragma once
#include <algorithm>

#include "../../../Frame/Frame.h"
#include "GameObject.h"
#include "Collider.h"


class DynamicObject : public GameObject
{
protected:
	enum class Collision {
		Left,
		Right,
		Top,
		Bottom
	};

	float fMass = 1.0f;
	sf::Vector2f fForceVector;
	Collider fCollider;

	bool fVerticalInWindowLock = false;
	bool fHorizontalInWindowLock = false;

	void applyWorldForces();
	sf::Vector2f checkCollisions(const sf::Vector2f& p);
	sf::Vector2f lockInFrame(const sf::Vector2f & p);
	virtual sf::Vector2f onCollision(const sf::Vector2f & p, GameObject * obj, const Collision & c, const sf::FloatRect & z, const sf::FloatRect & o);
	virtual sf::Vector2f onTrigger(const sf::Vector2f& p, GameObject * obj, const Collision& c, const sf::FloatRect& z, const sf::FloatRect& o) = 0;

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

