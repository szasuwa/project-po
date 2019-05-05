#include "Collider.h"


void Collider::resetCollider() 
{
	fLeft = fRight = fTop = fBottom = false;
}

void Collider::triggerLeft()
{
	fLeft = true;
}

bool Collider::getLeft() const 
{
	return fLeft;
}

void Collider::triggerRight()
{
	fRight = true;
}

bool Collider::getRight() const 
{
	return fRight;
}

void Collider::triggerTop() 
{
	fTop = true;
}

bool Collider::getTop() const
{
	return fTop;
}

void Collider::triggerBottom()
{
	fBottom = true;
}

bool Collider::getBottom() const 
{
	return fBottom;
}