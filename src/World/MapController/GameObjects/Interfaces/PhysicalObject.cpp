#include "PhysicalObject.h"
#include "../../Maps/Map.h"


PhysicalObject::PhysicalObject(Map * map) : PhysicalObject(sf::Vector2f(0,0), map)
{
}

PhysicalObject::PhysicalObject(const sf::Vector2f & position, Map * map) : PhysicalObject(position, false, false, map)
{
}

PhysicalObject::PhysicalObject(bool vLock, bool hLock, Map * map) : PhysicalObject(sf::Vector2f(0,0), vLock, hLock, map)
{
}

PhysicalObject::PhysicalObject(const sf::Vector2f & position, bool vLock, bool hLock, Map * map) : GameObject(map), 
	fForceVector(0, 0), fVerticalInWindowLock(vLock), fHorizontalInWindowLock(hLock), fMass(1)
{
}

PhysicalObject::PhysicalObject(const PhysicalObject &obj) : GameObject(obj)
{
	fForceVector = obj.fForceVector;
	fCollider = obj.fCollider;
	fVerticalInWindowLock = obj.fVerticalInWindowLock;
	fHorizontalInWindowLock = obj.fHorizontalInWindowLock;
}


PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::applyWorldForces()
{
	if (fMap == nullptr)
		return;

	if (!fCollider.getBottom()) {
		fForceVector.y += (*fMap).fGravityRate;
		fForceVector.y = std::min(fForceVector.y, (*fMap).fMaxGravityForce);
	}

	if (fForceVector.x > 0)
	{
		fForceVector.x = std::max(fForceVector.x - (*fMap).fDecelerationRate, 0.0f);
	}
	else if (fForceVector.x < 0)
	{
		fForceVector.x = std::min(fForceVector.x + (*fMap).fDecelerationRate, 0.0f);
	}
}

void PhysicalObject::checkCollisions() {
	if (fMap == nullptr)
		return;

	fCollider.resetCollider();

	for (GameObject* obj : fMap->getGameObjects()) 
	{
		if (obj != nullptr) {
			checkCollision(*obj);
		}
	}
}

void PhysicalObject::checkCollision(const GameObject & obj) {
	if (&obj == this || fMap == nullptr)
		return;

	sf::FloatRect cBounds = getGlobalBounds();
	sf::FloatRect nBounds = cBounds;
	float dTime = Frame::getInstance().getFrameTime();

	nBounds.left += fForceVector.x*dTime;
	nBounds.top += fForceVector.y*dTime;

	sf::FloatRect oBounds = obj.getGlobalBounds();

	if (nBounds.intersects(oBounds) && (obj.getClassType() == GameObjectClassType::PLAYER || obj.getClassType() == GameObjectClassType::PLATFORM)) {
		fForceVector.x = fCollider.handleHorizontalCollision(fForceVector.x, (*fMap).fDecelerationSmoothRate, dTime, cBounds, oBounds);

		nBounds.left = cBounds.left + fForceVector.x*dTime;

		if (nBounds.intersects(oBounds)) {
			float force = fForceVector.y;
			fForceVector.y = fCollider.handleVerticalCollision(fForceVector.y, (*fMap).fDecelerationSmoothRate, dTime, cBounds, oBounds);

			//Temporary fix for unstable bottom collision
			if (force > fForceVector.y) {
				fForceVector.y += (*fMap).fGravityRate;
			}
		}
	}
}

void PhysicalObject::applyForces() 
{
	applyWorldForces();
	checkCollisions();

	float dTime = Frame::getInstance().getFrameTime();
	MapBoundaries mb = fMap->getBoundaries();

	//Prevent escaping window boundaries
	if (fVerticalInWindowLock || fHorizontalInWindowLock) 
	{
		sf::FloatRect bounds = getGlobalBounds();

		if (fVerticalInWindowLock) {
			if (mb.hasTop && bounds.top + fForceVector.y*dTime < mb.top)
			{
				fCollider.triggerCollision(0, 0, 1, 0);
				fForceVector.y = mb.top - bounds.top;
			}

			if (mb.hasBottom && bounds.top + bounds.height + fForceVector.y*dTime > mb.bottom) 
			{
				fCollider.triggerCollision(0, 0, 0, 1);
				fForceVector.y = mb.bottom - bounds.top - bounds.height;
			}
		}
		
		if (fHorizontalInWindowLock) 
		{
			if (mb.hasLeft && bounds.left + fForceVector.x*dTime < 0) 
			{
				fCollider.triggerCollision(1, 0, 0, 0);
				fForceVector.x = mb.left-bounds.left;
			}

			if (mb.hasRight && bounds.left + bounds.width + fForceVector.x*dTime > mb.right) 
			{
				fCollider.triggerCollision(0, 1, 0, 0);
				fForceVector.x = mb.right - bounds.left - bounds.width;
			}
		}
	}

	//Set position
	move(fForceVector * dTime);
}

void PhysicalObject::serializeObject(std::ostream & ss) const {
	GameObject::serializeObject(ss);
	ss << fMass << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getLeft() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getRight() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getTop() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getBottom() << SERIALIZABLE_FIELD_DELIMITER;
}

void PhysicalObject::deserializeObject(std::istream & ss) {
	GameObject::deserializeObject(ss);
	ss >> fMass;
	ss >> fForceVector.x;
	ss >> fForceVector.y;

	bool l, r, t, b;
	ss >> l;
	ss >> r;
	ss >> t;
	ss >> b;
	fCollider.triggerCollision(l, r, t, b);
}