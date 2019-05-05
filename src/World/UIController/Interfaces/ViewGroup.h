#pragma once
#include <vector>
#include <SFML/system/Vector2.hpp>

#include "ViewItem.h"
#include "ViewAlignment.h"
#include "../../Interfaces/UIInterface.h"


class ViewGroup {
protected:
	UIInterface& fUIInterface;
	bool fVisible;
	sf::Vector2f fPosition;
	std::vector<ViewItem *> fItemList;
	ViewAlignment fAlignment = ViewAlignment::Left;

public:
	explicit ViewGroup(UIInterface& f);
	ViewGroup(UIInterface& f, const ViewAlignment & a);

	virtual void update();
	virtual void draw() const;

	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f& p);

	float calculateHeight() const;
	float calculateWidth() const;
	void calculatePositions();

	bool getVisibility() const;
	void setVisibility(const bool &v);
	void toggleVisibility();

	ViewAlignment getAlignment() const;
	void setAlignment(const ViewAlignment& a);
};