#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../Interfaces/FrameInterface.h"
#include "../../Interfaces/UIInterface.h"


class ViewItem {
protected:
	bool fVisible = true;

public:
	virtual void draw(UIInterface& f) const = 0;
	virtual void update(UIInterface& f) = 0;

	virtual void setPosition(const sf::Vector2f & p) = 0;
	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;

	bool getVisibility() const;
	void setVisibility(bool v);
};