#pragma once
#include <algorithm>
#include<SFML/Graphics/Rect.hpp>


class Collider
{
	bool fLeft = false;
	bool fRight = false;
	bool fTop = false;
	bool fBottom = false;

public:
	void resetCollider();
	void triggerLeft();
	void triggerRight();
	void triggerTop();
	void triggerBottom();
	bool getLeft() const;
	bool getRight() const;
	bool getTop() const;
	bool getBottom() const;
	
	float handleVerticalCollision(float speed, float smooth, float dTime, const sf::FloatRect & obj, const sf::FloatRect & col);
	float handleHorizontalCollision(float speed, float smooth, float dTime, const sf::FloatRect & obj, const sf::FloatRect & col);
};

