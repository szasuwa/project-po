#include "PhysicalObject.h"
#include "GameEngine.h"

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

void PhysicalObject::handleCollisions() {
	fCollisionSensor.resetSensor();
	sf::FloatRect bounds = getGlobalBounds();
	sf::FloatRect newBonds = bounds;
	newBonds.left += fForceVector.x*GameEngine::getFrameTime();
	newBonds.top += fForceVector.y*GameEngine::getFrameTime();

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
					newBonds.left = bounds.left + fForceVector.x*GameEngine::getFrameTime();
				}
				
				newRightCollision = (newBonds.left + newBonds.width > objBounds.left && newBonds.left < objBounds.left);
				rightCollision = (bounds.left + bounds.width > objBounds.left && bounds.left < objBounds.left);
				if (newRightCollision & !rightCollision)
				{
					fForceVector.x = std::min(fForceVector.x, 0.0f);
					newBonds.left = bounds.left + fForceVector.x*GameEngine::getFrameTime();
				}

				while (newBonds.intersects(objBounds)) {
					newTopCollision = (newBonds.top > objBounds.top && newBonds.top < objBounds.top + objBounds.height);
					newBottomCollision = (newBonds.top + newBonds.height > objBounds.top && newBonds.top + newBonds.height < objBounds.top + objBounds.height);
					
					if (newTopCollision)
					{
						fForceVector.y += fDecelerationSmoothRate;
						//fForceVector.y = std::max(fForceVector.y, 0.0f);
						newBonds.top = bounds.top + fForceVector.y*GameEngine::getFrameTime();
					}

					if (newBottomCollision)
					{
						fForceVector.y -= fDecelerationSmoothRate;
						//fForceVector.y = std::min(fForceVector.y, 0.0f);
						newBonds.top = bounds.top + fForceVector.y*GameEngine::getFrameTime();
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
	
	if (bounds.top + fForceVector.y*GameEngine::getFrameTime() < 0) {
		fForceVector.y = -bounds.top;
	}

	if (bounds.top + bounds.height + fForceVector.y*GameEngine::getFrameTime() > GameEngine::F_WINDOW_SIZE.y) {
		fForceVector.y = GameEngine::F_WINDOW_SIZE.y - bounds.top - bounds.height;
	}

	if (bounds.left + fForceVector.x*GameEngine::getFrameTime() < 0) {
		fForceVector.x = -bounds.left;
	}

	if (bounds.left +bounds.width + fForceVector.x*GameEngine::getFrameTime() > GameEngine::F_WINDOW_SIZE.x) {
		fForceVector.x = GameEngine::F_WINDOW_SIZE.x - bounds.left - bounds.width;
	}

	//Set position

	getTransformable()->move(fForceVector*GameEngine::getFrameTime());
}