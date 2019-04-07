#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


class InterfaceItem {
protected:
	bool fVisible = true;
public:
	virtual sf::Drawable * getDrawable() = 0;
	virtual void setPosition(sf::Vector2f &pos) = 0;
	virtual float getWidth() = 0;
	virtual float getHeight() = 0;
	void setVisibility(bool v);
	bool getVisibility();
};