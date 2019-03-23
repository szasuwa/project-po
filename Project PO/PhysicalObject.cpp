#include "PhysicalObject.h"
#include "GameEngine.h"
#include "World.h"

float PhysicalObject::fDecelerationRate = 15.f;
float PhysicalObject::fDecelerationSmoothRate = 0.1f;
float PhysicalObject::fGravityRate = 15.f;
float PhysicalObject::fGravityForce = 500.f;


PhysicalObject::PhysicalObject()
{
	fForceVector.x = 0;
	fForceVector.y = 0;
}


PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::serializeData(std::stringstream &ss, bool last) {
	GameObject::serializeData(ss);
	ss << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollisionSensor.getLeft() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollisionSensor.getRight() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollisionSensor.getTop() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollisionSensor.getBottom();
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
	fCollisionSensor.triggerCollision(l, r, t, b);
}

void PhysicalObject::handleCollisions() {
	fCollisionSensor.resetSensor();
	sf::FloatRect bounds = getGlobalBounds();
	sf::FloatRect newBounds = bounds;

	newBounds.left += fForceVector.x*GameEngine::getFrameTime();
	newBounds.top += fForceVector.y*GameEngine::getFrameTime();

	for (GameObject* obj : World::getGameObjectList()) 
	{
		if (obj->getId() != fId) {
			if (newBounds.intersects(obj->getGlobalBounds())) {
				sf::FloatRect objBounds = obj->getGlobalBounds();

				bool newLeftCollision = false,
					leftCollision = false,
					newRightCollision = false,
					rightCollision = false,
					newTopCollision = false,
					bottomCollision = false,
					newBottomCollision = false;

				newLeftCollision = (newBounds.left < objBounds.left + objBounds.width && newBounds.left + newBounds.width > objBounds.left + objBounds.width);
				leftCollision = (bounds.left < objBounds.left + objBounds.width && bounds.left + bounds.width > objBounds.left + objBounds.width);
				if (newLeftCollision & !leftCollision)
				{
					fForceVector.x = std::max(fForceVector.x, 0.0f);
					newBounds.left = bounds.left + fForceVector.x*GameEngine::getFrameTime();
				}
				
				newRightCollision = (newBounds.left + newBounds.width > objBounds.left && newBounds.left < objBounds.left);
				rightCollision = (bounds.left + bounds.width > objBounds.left && bounds.left < objBounds.left);
				if (newRightCollision & !rightCollision)
				{
					fForceVector.x = std::min(fForceVector.x, 0.0f);
					newBounds.left = bounds.left + fForceVector.x*GameEngine::getFrameTime();
				}

				bottomCollision = (newBounds.top + newBounds.height > objBounds.top && newBounds.top + newBounds.height < objBounds.top + objBounds.height);
				while (newBounds.intersects(objBounds)) {
					newTopCollision = (newBounds.top > objBounds.top && newBounds.top < objBounds.top + objBounds.height);
					newBottomCollision = (newBounds.top + newBounds.height > objBounds.top && newBounds.top + newBounds.height < objBounds.top + objBounds.height);
					
					if (newTopCollision)
					{
						fForceVector.y += fDecelerationSmoothRate;
						newBounds.top = bounds.top + fForceVector.y*GameEngine::getFrameTime();
					}

					if (newBottomCollision)
					{
						fForceVector.y -= fDecelerationSmoothRate;
						newBounds.top = bounds.top + fForceVector.y*GameEngine::getFrameTime();
					}
				}

				//Temporary fix for unstable bottom collision
				if (bottomCollision) {
					fForceVector.y += fGravityRate;
				}
				fCollisionSensor.triggerCollision(newLeftCollision & !leftCollision, newRightCollision & !rightCollision, newTopCollision, newBottomCollision | bottomCollision);
			}
		}
	}
}

void PhysicalObject::applyGravity() {
	if (!fCollisionSensor.getBottom()) {
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
	sf::FloatRect bounds = getGlobalBounds();
	
	if (bounds.top + fForceVector.y*GameEngine::getFrameTime() < 0) {
		fCollisionSensor.triggerCollision(0, 0, 1, 0);
		fForceVector.y = -bounds.top;
	}

	if (bounds.top + bounds.height + fForceVector.y*GameEngine::getFrameTime() > GameEngine::getWindowSize().y) {
		fCollisionSensor.triggerCollision(0, 0, 0, 1);
		fForceVector.y = GameEngine::getWindowSize().y - bounds.top - bounds.height;
	}

	if (bounds.left + fForceVector.x*GameEngine::getFrameTime() < 0) {
		fCollisionSensor.triggerCollision(1, 0, 0, 0);
		fForceVector.x = -bounds.left;
	}

	if (bounds.left +bounds.width + fForceVector.x*GameEngine::getFrameTime() > GameEngine::getWindowSize().x) {
		fCollisionSensor.triggerCollision(0, 1, 0, 0);
		fForceVector.x = GameEngine::getWindowSize().x - bounds.left - bounds.width;
	}

	//Set position

	getTransformable()->move(fForceVector*GameEngine::getFrameTime());
}