#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "../Interfaces/ViewItem.h"


class SeparatorViewItem : public ViewItem {
protected:
	float fHeight;

public:
	SeparatorViewItem(UIInterface& f, float h = 10);
	

	virtual void update();
	virtual void draw() const;

	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};