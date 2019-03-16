#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
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

	bool getLeft() 
	{
		return fLeft;
	}

	bool getRight()
	{
		return fRight;
	}

	bool getTop()
	{
		return fTop;
	}

	bool getBottom()
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

	void applyDeceleration();
	void applyGravity();
	void handleCollisions();
public:
	PhysicalObject();
	~PhysicalObject();

	void handleForces();
};

