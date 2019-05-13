#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "../Interfaces/ViewItem.h"
#include "../../Frame/Frame.h"
#include "../../../GameConstants.h"
#include "../../TextObject.h"


class TextViewItem : public ViewItem {
protected:
	static float F_TEXT_HEIGHT_OFFSET;
	TextObject fText;

public:
	TextViewItem();

	virtual void update(GameEngineInterface& f);
	virtual void draw(GameEngineInterface& f) const;

	void setText(const std::string& txt);
	void setColor(const sf::Color& c);
	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};