#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "../Interfaces/ViewItem.h"


class SeparatorViewItem : public ViewItem {
protected:
	float fHeight;

public:
	explicit SeparatorViewItem(float h = 10);
	

	virtual void update(GameEngineInterface& f);
	virtual void draw(GameEngineInterface& f) const;

	virtual void setPosition(const sf::Vector2f & p);
	virtual float getWidth() const;
	virtual float getHeight() const;
};