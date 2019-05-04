#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "../Interfaces/ViewItem.h"
#include "../../Frame/Frame.h"


class TextViewItem : public ViewItem {
protected:
	static float F_TEXT_HEIGHT_OFFSET;
	sf::Text fText;

public:
	TextViewItem();
	void setText(const std::string &txt);
	virtual void draw() const;
	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};