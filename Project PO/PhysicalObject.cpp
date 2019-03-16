#include "PhysicalObject.h"
#include "GameEngine.h"

float PhysicalObject::fDecelerationRate = 0.01f;
float PhysicalObject::fGravityRate = 0.005f;
float PhysicalObject::fGravityForce = 0.5f;


PhysicalObject::PhysicalObject()
{
	fForceVector.x = 0;
	fForceVector.y = 0;
}


PhysicalObject::~PhysicalObject()
{
}

void PhysicalObject::handleCollisions() {
	fCollisionSensor.resetSensor();
	sf::FloatRect bounds = getGlobalBounds();
	sf::FloatRect newBonds = bounds;
	newBonds.left += fForceVector.x;
	newBonds.top += fForceVector.y;

	for (GameObject* obj : GameEngine::getGameObjectList()) 
	{
		if (obj->getId() != fId) {
			if (newBonds.intersects(obj->getGlobalBounds())) {
				sf::FloatRect objBounds = obj->getGlobalBounds();

				bool newLeftCollision = false,
					leftCollision = false,
					newRightCollision = false,
					rightCollision = false,
					newTopCollision = false,
					newBottomCollision = false;

				newLeftCollision = (newBonds.left < objBounds.left + objBounds.width && newBonds.left + newBonds.width > objBounds.left + objBounds.width);
				leftCollision = (bounds.left < objBounds.left + objBounds.width && bounds.left + bounds.width > objBounds.left + objBounds.width);
				if (newLeftCollision & !leftCollision)
				{
					fForceVector.x = std::max(fForceVector.x, 0.0f);
					newBonds.left = bounds.left + fForceVector.x;
				}
				
				newRightCollision = (newBonds.left + newBonds.width > objBounds.left && newBonds.left < objBounds.left);
				rightCollision = (bounds.left + bounds.width > objBounds.left && bounds.left < objBounds.left);
				if (newRightCollision & !rightCollision)
				{
					fForceVector.x = std::min(fForceVector.x, 0.0f);
					newBonds.left = bounds.left + fForceVector.x;
				}

				if (newBonds.intersects(objBounds)) {
					newTopCollision = (newBonds.top > objBounds.top && newBonds.top < objBounds.top + objBounds.height);
					newBottomCollision = (newBonds.top + newBonds.height > objBounds.top && newBonds.top + newBonds.height < objBounds.top + objBounds.height);
					
					if (newTopCollision)
					{
						fForceVector.y = std::max(fForceVector.y, 0.0f);
						newBonds.top = bounds.top + fForceVector.y;
					}

					if (newBottomCollision)
					{
						fForceVector.y = std::min(fForceVector.y, 0.0f);
						newBonds.top = bounds.top + fForceVector.y;
					}
				}

				fCollisionSensor.triggerCollision(newLeftCollision & !leftCollision, newRightCollision & !rightCollision, newTopCollision, newBottomCollision);
			}
		}
	}
}

void PhysicalObject::applyGravity() {
	fForceVector.y += fGravityRate;
	fForceVector.y = std::min(fForceVector.y, fGravityForce);
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
	
	if (bounds.top + fForceVector.y < 0) {
		fForceVector.y = -bounds.top;
	}

	if (bounds.top + bounds.height + fForceVector.y > GameEngine::F_WINDOW_SIZE.y) {
		fForceVector.y = GameEngine::F_WINDOW_SIZE.y - bounds.top - bounds.height;
	}

	if (bounds.left + fForceVector.x < 0) {
		fForceVector.x = -bounds.left;
	}

	if (bounds.left +bounds.width + fForceVector.x > GameEngine::F_WINDOW_SIZE.x) {
		fForceVector.x = GameEngine::F_WINDOW_SIZE.x - bounds.left - bounds.width;
	}

	//Set position
	getTransformable()->move(fForceVector);
}