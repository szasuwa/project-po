#include "PhysicalObject.h"
#include "../../Map/Bases/Map.h"

float PhysicalObject::fDecelerationRate = 15.f;
float PhysicalObject::fDecelerationSmoothRate = 0.1f;
float PhysicalObject::fGravityRate = 15.f;
float PhysicalObject::fGravityForce = 500.f;

PhysicalObject::PhysicalObject(Map* map) : PhysicalObject(sf::Vector2f(0,0), map)
{
}

PhysicalObject::PhysicalObject(const sf::Vector2f &position, Map* map) : PhysicalObject(position, false, false, map)
{
}

PhysicalObject::PhysicalObject(bool boundsV, bool boundsH, Map* map) : PhysicalObject(sf::Vector2f(0,0), boundsV, boundsH, map)
{
}

PhysicalObject::PhysicalObject(const sf::Vector2f &position, bool boundsV, bool boundsH, Map* map) : GameObject(position, map)
{
	fForceVector.x = 0;
	fForceVector.y = 0;
	fInWindowBoundsVertical = boundsV;
	fInWindowBoundsHorizontal = boundsH;
}

PhysicalObject::PhysicalObject(const PhysicalObject &obj) : GameObject(obj)
{
	fForceVector = obj.fForceVector;
	fCollider = obj.fCollider;
	fInWindowBoundsVertical = obj.fInWindowBoundsVertical;
}


PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::serializeData(std::stringstream &ss, bool last) {
	GameObject::serializeData(ss);
	ss << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.isLeft() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.isRight() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.isTop() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.isBottom();
	Serializable::serializeData(ss, last);
}

void PhysicalObject::deserializeData(std::stringstream &ss) {
	GameObject::deserializeData(ss);
	ss >> fForceVector.x;
	ss >> fForceVector.y;

	bool l, r, t, b;
	ss >> l;
	ss >> r;
	ss >> t;
	ss >> b;
	fCollider.triggerCollision(l, r, t, b);
}

void PhysicalObject::handleCollisions() {
	if (fMap == nullptr)
		return;

	fCollider.resetCollider();

	for (GameObject* obj : fMap->getGameObjectList()) 
	{
		checkCollision(obj);
	}
}

void PhysicalObject::checkCollision(GameObject* obj) {
	if (obj == this)
		return;

	sf::FloatRect cBounds = getGlobalBounds();
	sf::FloatRect nBounds = cBounds;

	nBounds.left += fForceVector.x*Frame::getFrameTime();
	nBounds.top += fForceVector.y*Frame::getFrameTime();

	sf::FloatRect oBounds = obj->getGlobalBounds();

	if (nBounds.intersects(oBounds) && (obj->getClassType() == CLASS_TYPE::PLAYER || obj->getClassType() == CLASS_TYPE::PLATFORM)) {
		fForceVector.x = fCollider.checkHorizontal(fForceVector.x, fDecelerationSmoothRate, Frame::getFrameTime(), cBounds.left, cBounds.width, oBounds.left, oBounds.width);

		nBounds.left = cBounds.left + fForceVector.x*Frame::getFrameTime();

		if (nBounds.intersects(oBounds)) {
			float force = fForceVector.y;
			fForceVector.y = fCollider.checkVertical(fForceVector.y, fDecelerationSmoothRate, Frame::getFrameTime(), cBounds.top, cBounds.height, oBounds.top, oBounds.height);

			//Temporary fix for unstable bottom collision
			if (force > fForceVector.y) {
				fForceVector.y += fGravityRate;
			}
		}
	}
}

void PhysicalObject::applyGravity() {
	if (!fCollider.isBottom()) {
		fForceVector.y += fGravityRate;
		fForceVector.y = std::min(fForceVector.y, fGravityForce);
	}	
}

void PhysicalObject::applyDeceleration() {
	if (fForceVector.x > 0) 
	{
		fForceVector.x = std::max(fForceVector.x - fDecelerationRate, 0.0f);
	}
	else if (fForceVector.x < 0) 
	{
		fForceVector.x = std::min(fForceVector.x + fDecelerationRate, 0.0f);
	}
}

void PhysicalObject::handleForces() 
{
	applyGravity();
	applyDeceleration();
	handleCollisions();

	//Prevent escaping window boundaries
	if (fInWindowBoundsVertical || fInWindowBoundsHorizontal) {
		sf::FloatRect bounds = getGlobalBounds();

		if (fInWindowBoundsVertical) {
			if (bounds.top + fForceVector.y*Frame::getFrameTime() < 0) {
				fCollider.triggerCollision(0, 0, 1, 0);
				fForceVector.y = -bounds.top;
			}

			if (bounds.top + bounds.height + fForceVector.y*Frame::getFrameTime() > Frame::getWindowHeight()) {
				fCollider.triggerCollision(0, 0, 0, 1);
				fForceVector.y = Frame::getWindowHeight() - bounds.top - bounds.height;
			}
		}
		
		if (fInWindowBoundsHorizontal) {
			if (bounds.left + fForceVector.x*Frame::getFrameTime() < 0) {
				fCollider.triggerCollision(1, 0, 0, 0);
				fForceVector.x = -bounds.left;
			}

			if (bounds.left + bounds.width + fForceVector.x*Frame::getFrameTime() > Frame::getWindowWidth()) {
				fCollider.triggerCollision(0, 1, 0, 0);
				fForceVector.x = Frame::getWindowWidth() - bounds.left - bounds.width;
			}
		}
	}

	//Set position
	getTransformable()->move(fForceVector*Frame::getFrameTime());
}