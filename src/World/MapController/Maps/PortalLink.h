#pragma once
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../../GameConstants.h"


class PortalLink : public sf::Drawable, public sf::Transformable {
	float fPointSize = 5;

	sf::Vertex fLine[2];
	sf::Vertex fPoint[2][2];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	PortalLink();
	PortalLink(const sf::Vector2f& p1, const sf::Vector2f& p2);
	void update(const sf::Vector2f& p1, const sf::Vector2f& p2);
};