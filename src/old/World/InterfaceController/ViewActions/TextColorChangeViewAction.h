#pragma once
#include <SFML/graphics/color.hpp>

#include "../ViewItems/TextViewItem.h"


class TextColorChangeViewAction : public ViewAction {
	sf::Color fColor;
	TextViewItem& fItem;

public:
	explicit TextColorChangeViewAction(const sf::Color& c, TextViewItem & i):fColor(c), fItem(i) {};
	virtual void operator() () { fItem.setColor(fColor); };
};