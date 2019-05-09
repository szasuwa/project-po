#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "ViewItem.h"
#include "ViewAlignment.h"
#include "../../Interfaces/GameEngineInterface.h"


class ViewGroup {
protected:
	bool fVisible;
	sf::Vector2f fPosition;
	std::vector<ViewItem *> fItemList;
	ViewAlignment fAlignment = ViewAlignment::Left;

public:
	explicit ViewGroup(const ViewAlignment & a);

	virtual void update(GameEngineInterface& f);
	virtual void draw(GameEngineInterface& f) const;

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