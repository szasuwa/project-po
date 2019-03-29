#include "Collider.h"

Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::resetCollider() {
	fLeft = fRight = fTop = fBottom = false;
}

void Collider::triggerCollision(bool l, bool r, bool t, bool b) {
	fLeft = l;
	fRight = r;
	fTop = t;
	fBottom = b;
}

bool Collider::isLeft() {
	return fLeft;
}

bool Collider::isRight() {
	return fRight;
}

bool Collider::isTop() {
	return fTop;
}

bool Collider::isBottom() {
	return fBottom;
}

float Collider::checkHorizontal(float speed, float deceleration, float dTime, float oPos, float oWidth, float cPos, float cWidth) {
	float nPos = oPos + speed * dTime;

	bool newLeftCollision, leftCollision, newRightCollision, rightCollision;

	newLeftCollision = (nPos < cPos + cWidth && nPos + oWidth > cPos + cWidth);
	leftCollision = (oPos < cPos + cWidth && oPos + oWidth > cPos + cWidth);
	if (newLeftCollision & !leftCollision)
	{
		
		speed = std::max(speed, 0.0f);
		nPos = oPos + speed * dTime;
	}

	newRightCollision = (nPos + oWidth > cPos && nPos < cPos);
	rightCollision = (oPos + oWidth > cPos && oPos < oWidth);
	if (newRightCollision & !rightCollision)
	{
		speed = std::min(speed, 0.0f);
	}

	fLeft |= newLeftCollision & !leftCollision;
	fRight |= newRightCollision & !rightCollision;
	return speed;
}

float Collider::checkVertical(float speed, float deceleration, float dTime, float oPos, float oHeight, float cPos, float cHeight) {
	float nPos = oPos + speed * dTime;

	bool newTopCollision = false,
		bottomCollision = false,
		newBottomCollision = false;

	bottomCollision = (nPos + oHeight > cPos && nPos + oHeight < cPos + cHeight);

	do {
		newTopCollision = (nPos > cPos && nPos < cPos + cHeight);
		newBottomCollision = (nPos + oHeight > cPos && nPos + oHeight < cPos + cHeight);

		if (newTopCollision)
		{
			speed += deceleration;
			nPos = oPos + speed * dTime;
		}

		if (newBottomCollision)
		{
			speed -= deceleration;
			nPos = oPos + speed * dTime;
		}
	} while (newTopCollision || newBottomCollision);

	fTop |= newTopCollision;
	fBottom |= newBottomCollision | bottomCollision;
	return speed;	
}
