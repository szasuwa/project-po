#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "../Interfaces/ViewItem.h"


class SeparatorViewItem : public ViewItem {
protected:
	float fHeight;

public:
	explicit SeparatorViewItem(float h = 50);
	virtual void draw() const;
	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};