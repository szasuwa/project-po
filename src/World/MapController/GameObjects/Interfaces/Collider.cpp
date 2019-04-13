#include "Collider.h"


void Collider::resetCollider() 
{
	fLeft = fRight = fTop = fBottom = false;
}

void Collider::triggerCollision(bool l, bool r, bool t, bool b) 
{
	fLeft |= l;
	fRight |= r;
	fTop |= t;
	fBottom |= b;
}

bool Collider::getLeft() const 
{
	return fLeft;
}

bool Collider::getRight() const 
{
	return fRight;
}

bool Collider::getTop() const
{
	return fTop;
}

bool Collider::getBottom() const 
{
	return fBottom;
}

float Collider::handleVerticalCollision(float speed, float smooth, float dTime, const sf::FloatRect & obj, const sf::FloatRect & col)
{
	sf::FloatRect nObj = obj;
	nObj.top += speed * dTime;

	bool newTopCollision = false,
		bottomCollision = false,
		newBottomCollision = false;

	bottomCollision = (nObj.top + nObj.height > col.top && nObj.top + nObj.height < col.top + col.height);

	do {
		newTopCollision = (nObj.top > col.top && nObj.top < col.top + col.height);
		newBottomCollision = (nObj.top + nObj.height > col.top && nObj.top + nObj.height < col.top + col.height);

		if (newTopCollision)
		{
			speed += smooth;
			nObj.top = obj.top + speed * dTime;
		}

		if (newBottomCollision)
		{
			speed -= smooth;
			nObj.top = obj.top + speed * dTime;
		}
	} while (newTopCollision || newBottomCollision);

	fTop |= newTopCollision;
	fBottom |= newBottomCollision | bottomCollision;
	return speed;	
}


float Collider::handleHorizontalCollision(float speed, float smooth, float dTime, const sf::FloatRect & obj, const sf::FloatRect & col)
{
	sf::FloatRect nObj = obj;
	nObj.left += speed * dTime;

	bool newLeftCollision, leftCollision, newRightCollision, rightCollision;

	newLeftCollision = (nObj.left < col.left + col.width && nObj.left + nObj.width > col.left + col.width);
	leftCollision = (obj.left < col.left + col.width && obj.left + nObj.width > col.left + col.width);
	if (newLeftCollision & !leftCollision)
	{

		speed = std::max(speed, 0.0f);
		nObj.left = obj.left + speed * dTime;
	}

	newRightCollision = (nObj.left + nObj.width > col.left && nObj.left < col.left);
	rightCollision = (obj.left + nObj.width > col.left && obj.left < nObj.width);
	if (newRightCollision & !rightCollision)
	{
		speed = std::min(speed, 0.0f);
	}

	fLeft |= newLeftCollision & !leftCollision;
	fRight |= newRightCollision & !rightCollision;
	return speed;
}