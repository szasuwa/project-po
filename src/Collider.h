#pragma once
#include <algorithm>

class Collider
{
	bool fLeft = false;
	bool fRight = false;
	bool fTop = false;
	bool fBottom = false;


public:
	Collider();
	~Collider();

	void resetCollider();
	void triggerCollision(bool l, bool r, bool t, bool b);
	bool isLeft();
	bool isRight();
	bool isTop();
	bool isBottom();
	
	float checkHorizontal(float speed, float deceleration, float dTime, float oPos, float oWidth, float cPos, float cWidth);
	float checkVertical(float speed, float deceleration, float dTime, float oPos, float oHeight, float cPos, float cHeight);
};

