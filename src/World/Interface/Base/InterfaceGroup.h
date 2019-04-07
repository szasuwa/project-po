#pragma once
#include <vector>

#include "InterfaceItem.h"
#include "../../Frame.h"


class InterfaceGroup {
public:
	enum Alignment {
		Left,
		Right,
		Center
	};

protected:
	bool fVisible;
	Alignment fAlignment;
	std::vector<InterfaceItem *> fItemList;

public:
	void drawGroup(sf::RenderWindow &window);
	float calculateHeight();
	float calculateWidth();
	void calculatePositions(float offset);
	virtual void update() = 0;
	bool getVisibility();
	void setVisibility(bool v);
	Alignment getAlignment();
	void setAlignment(Alignment align);
};