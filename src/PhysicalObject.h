#pragma once
#include "GameObject.h"
#include "Frame.h"
#include <algorithm>

class CollisionSensor {
	bool fLeft = false;
	bool fRight = false; 
	bool fTop = false; 
	bool fBottom = false;

public:
	CollisionSensor() {};
	~CollisionSensor() {};
	
	void resetSensor() 
	{
		fLeft = false;
		fRight = false;
		fTop = false;
		fBottom = false;
	};

	void triggerCollision(bool l, bool r, bool t, bool b) 
	{
		fLeft |= l;
		fRight |= r;
		fTop |= t;
		fBottom |= b;
	}

	bool hasColided() 
	{
		return fLeft || fRight || fTop || fBottom;
	}

	bool getLeft() const
	{
		return fLeft;
	}

	bool getRight() const
	{
		return fRight;
	}

	bool getTop() const
	{
		return fTop;
	}

	bool getBottom() const
	{
		return fBottom;
	}
};

class PhysicalObject : public GameObject
{
protected:
	static float fDecelerationRate;
	static float fDecelerationSmoothRate;
	static float fGravityRate;
	static float fGravityForce;
	sf::Vector2f fForceVector;
	CollisionSensor fCollisionSensor;
	bool fInWindowBoundsVertical;
	bool fInWindowBoundsHorizontal;

	void applyDeceleration();
	void applyGravity();
	void handleCollisions();
public:
	PhysicalObject();
	PhysicalObject(bool boundsV, bool boundsH);
	~PhysicalObject();

	void serializeData(std::stringstream &ss, bool last = true);
	void deserializeData(std::stringstream &ss);

	void handleForces();
};

