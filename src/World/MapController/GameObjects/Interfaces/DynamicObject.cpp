#include "DynamicObject.h"
#include "../../Maps/Map.h"
#include <iostream>


DynamicObject::DynamicObject(Map * map) : DynamicObject(sf::Vector2f(0,0), map)
{
}

DynamicObject::DynamicObject(const sf::Vector2f & position, Map * map) : DynamicObject(position, false, false, map)
{
}

DynamicObject::DynamicObject(bool vLock, bool hLock, Map * map) : DynamicObject(sf::Vector2f(0,0), vLock, hLock, map)
{
}

DynamicObject::DynamicObject(const sf::Vector2f & position, bool vLock, bool hLock, Map * map) : GameObject(map), 
	fForceVector(0, 0), fVerticalInWindowLock(vLock), fHorizontalInWindowLock(hLock), fMass(1)
{
}

DynamicObject::DynamicObject(const DynamicObject &obj) : GameObject(obj)
{
	fForceVector = obj.fForceVector;
	fCollider = obj.fCollider;
	fVerticalInWindowLock = obj.fVerticalInWindowLock;
	fHorizontalInWindowLock = obj.fHorizontalInWindowLock;
}


DynamicObject::~DynamicObject()
{
}

void DynamicObject::applyWorldForces()
{
	if (fMap == nullptr)
		return;

	if (!fCollider.getBottom()) {
		fForceVector.y += (*fMap).fGravityRate;
		fForceVector.y = std::min(fForceVector.y, (*fMap).fMaxGravityForce);
	}

	if (fCollider.getTop() && fForceVector.y < 0)
		fForceVector.y = 0;

	if (fForceVector.x > 0)
	{
		fForceVector.x = std::max(fForceVector.x - (*fMap).fDecelerationRate, 0.0f);
	}
	else if (fForceVector.x < 0)
	{
		fForceVector.x = std::min(fForceVector.x + (*fMap).fDecelerationRate, 0.0f);
	}
}

sf::Vector2f DynamicObject::checkCollisions(const sf::Vector2f& p) {
	if (fMap == nullptr)
		return sf::Vector2f(0,0);

	sf::Vector2f out = p;
	fCollider.resetCollider();

	MapBoundaries mb = fMap->getBoundaries();
	sf::FloatRect b = getGlobalBounds();

	if (fHorizontalInWindowLock) 
	{
		if (mb.hasLeft && p.x < 0 && b.left + p.x < mb.left)
		{
			std::cout << "LM" << std::endl;
			fCollider.triggerLeft();
			out.x = std::min(mb.left - b.left, 0.f);
		}

		if (mb.hasRight && p.x > 0 && b.left + b.width + p.x > mb.right)
		{
			std::cout << "RM" << std::endl;
			fCollider.triggerRight();
			out.x = std::max(mb.right - b.left - b.width, 0.f);
		}
	}
	
	if (fVerticalInWindowLock) 
	{
		if (mb.hasTop && p.y < 0 && b.top + p.y < mb.top)
		{
			std::cout << "TM" << std::endl;
			fCollider.triggerTop();
			out.y = std::min(mb.top - b.top, 0.f);
		}

		if (mb.hasBottom && p.y > 0 && b.top + b.height + p.y > mb.bottom)
		{
			std::cout << "BM" << std::endl;
			fCollider.triggerBottom();
			out.y = std::max(mb.bottom - b.top - b.height, 0.f);
		}

	}

	for (GameObject* obj : fMap->getGameObjects()) 
	{
		if (obj == nullptr || obj == this || !obj->hasCollider())
			continue;
		
		sf::FloatRect o = obj->getGlobalBounds();
		sf::FloatRect d;

		//Check left
		if (!fCollider.getLeft() && p.x < 0)
		{
			d = sf::FloatRect(b.left, b.top, p.x, b.height);
			
			if (d.intersects(o))
			{
				std::cout << "L" << std::endl;
				fCollider.triggerLeft();
				out.x = std::min(o.left + o.width - d.left, 0.f);
			}
		}

		if (!fCollider.getRight() && p.x > 0)
		{
			d = sf::FloatRect(b.left + b.width, b.top, p.x, b.height);

			if (d.intersects(o))
			{
				std::cout << "R" << std::endl;
				fCollider.triggerRight();
				out.x = std::max(o.left - d.left, 0.f);
			}
		}

		if (!fCollider.getTop() && p.y < 0)
		{
			d = sf::FloatRect(b.left, b.top, b.width, p.y);

			if (d.intersects(o))
			{
				std::cout << "T" << std::endl;
				fCollider.triggerTop();
				out.y = std::min(o.top + o.height - d.top, 0.f);
			}

		}

		if (!fCollider.getBottom() && p.y > 0)
		{
			d = sf::FloatRect(b.left, b.top + b.height, b.width, p.y);

			if (d.intersects(o))
			{
				std::cout << "B" << std::endl;
				fCollider.triggerBottom();
				out.y = std::max(o.top - d.top, 0.f);
			}
		}
		
		/*
		else
			h = sf::FloatRect(b.left + b.width, b.top, p.x, b.height);

		if (p.y < 0)
			v = sf::FloatRect(b.left, b.top, b.width, p.y);
		else
			v = sf::FloatRect(b.left, b.top + b.height, b.width, p.y);
			*/
	}
	return out;
}

/*
void DynamicObject::checkCollision(const GameObject & obj) {
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
*/

void DynamicObject::applyForces() 
{
	applyWorldForces();
	//checkCollisions();

	float dTime = Frame::getInstance().getFrameTime();
	

	/*
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
	*/

	//Set position
	move(fForceVector * dTime);
}

void DynamicObject::serializeObject(std::ostream & ss) const {
	GameObject::serializeObject(ss);
	ss << fMass << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.x << SERIALIZABLE_FIELD_DELIMITER;
	ss << fForceVector.y << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getLeft() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getRight() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getTop() << SERIALIZABLE_FIELD_DELIMITER;
	ss << fCollider.getBottom() << SERIALIZABLE_FIELD_DELIMITER;
}

void DynamicObject::deserializeObject(std::istream & ss) {
	GameObject::deserializeObject(ss);
	ss >> fMass;
	ss >> fForceVector.x;
	ss >> fForceVector.y;

	float l, r, t, b;
	ss >> l;
	ss >> r;
	ss >> t;
	ss >> b;
	//fCollider.triggerCollision(l, r, t, b);
}

void DynamicObject::move(const sf::Vector2f& p, bool gridSnap, bool vLock, bool hLock)
{
	if (fTransformable == nullptr)
		return;

	fTransformable->move(checkCollisions(p));
}