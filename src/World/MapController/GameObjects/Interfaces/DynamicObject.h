#pragma once
#include <algorithm>

#include "../../../Frame/Frame.h"
#include "GameObject.h"
#include "Collider.h"


class DynamicObject : public GameObject
{
public:
	enum class Collision {
		None,
		Left,
		Right,
		Top,
		Bottom
	};

protected:
	static const std::string F_REGEX_DYNAMIC_OBJECT_PATTERN;

	float fMass = 1.0f;
	bool fIsStatic = false;
	sf::Vector2f fForceVector;
	sf::Vector2f fMovement;
	Collider fCollider;

	bool fVerticalInWindowLock = false;
	bool fHorizontalInWindowLock = false;

	void applyWorldForces();
	sf::Vector2f checkCollisions(const sf::Vector2f& p, const Collision& c = Collision::None);
	sf::Vector2f lockInFrame(const sf::Vector2f & p);
	virtual sf::Vector2f onCollision(const sf::Vector2f& p, DynamicObject * o, const Collision& c);
	virtual sf::Vector2f onCollision(const sf::Vector2f & p, GameObject * obj, const Collision & c, const sf::FloatRect & z, const sf::FloatRect & o);
	virtual sf::Vector2f onTrigger(const sf::Vector2f& p, GameObject * obj, const Collision& c, const sf::FloatRect& z, const sf::FloatRect& o) = 0;
public:
	DynamicObject(MapInterface& f, Map * m = nullptr);
	DynamicObject(MapInterface& f, const sf::Vector2f & position, Map * m = nullptr);
	DynamicObject(MapInterface& f, bool vLock, bool hLock, Map * m = nullptr);
	DynamicObject(MapInterface& f, const sf::Vector2f & position, bool vLock, bool hLock, Map * m = nullptr);
	DynamicObject(const DynamicObject & o);

	virtual void onUpdate();

	virtual void move(const sf::Vector2f& p);
	virtual void move(const sf::Vector2f& p, const Collision & c);

	virtual GameObjectInterfaceType getInterfaceType() const;
	virtual void serializeObject(std::ostream& ss) const;
	virtual void deserializeObject(std::istream& ss);
};

Collider& operator+=(Collider & o, const DynamicObject::Collision & c);