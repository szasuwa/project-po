#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "../Interfaces/ViewItem.h"
#include "../../Frame/Frame.h"
#include "../../../GameConstants.h"


class TextViewItem : public ViewItem {
protected:
	static float F_TEXT_HEIGHT_OFFSET;
	sf::Text fText;

public:
	TextViewItem();

	virtual void update(UIInterface& f);
	virtual void draw(UIInterface& f) const;

	void setText(const std::string& txt);
	void setColor(const sf::Color& c);
	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};