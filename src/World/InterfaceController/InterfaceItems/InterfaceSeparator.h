#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "InterfaceItem.h"


class InterfaceSeparator : public InterfaceItem {
	float fHeight;
public:
	explicit InterfaceSeparator(float h = 5);
	virtual void draw() const;
	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};