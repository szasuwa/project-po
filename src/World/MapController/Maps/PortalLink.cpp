#include "PortalLink.h"

PortalLink::PortalLink()
{
	fLine[0] = fLine[1] = fPoint[0][0] = fPoint[0][1] = fPoint[1][0] = fPoint[1][1] = sf::Vertex();
	fLine[0].color = PORTAL_LINK_LINE_COLOR_1;
	fLine[1].color = PORTAL_LINK_LINE_COLOR_2;

	fPoint[0][0].color = PORTAL_LINK_POINT_COLOR_1;
	fPoint[0][1].color = PORTAL_LINK_POINT_COLOR_2;
	fPoint[1][0].color = PORTAL_LINK_POINT_COLOR_3;
	fPoint[1][1].color = PORTAL_LINK_POINT_COLOR_4;
}

PortalLink::PortalLink(const sf::Vector2f& p1, const sf::Vector2f& p2) : PortalLink()
{
	update(p1, p2);
}

void PortalLink::update(const sf::Vector2f & p1, const sf::Vector2f& p2) {
	fLine[0].position = p1;
	fLine[1].position = p2;

	fPoint[0][0].position = p2 + sf::Vector2f(-fPointSize, -fPointSize);
	fPoint[0][1].position = p2 + sf::Vector2f(+fPointSize, +fPointSize);
	fPoint[1][0].position = p2 + sf::Vector2f(+fPointSize, -fPointSize);
	fPoint[1][1].position = p2 + sf::Vector2f(-fPointSize, +fPointSize);
}

void PortalLink::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(fLine, 2, sf::Lines, states);
	target.draw(fPoint[0], 2, sf::Lines, states);
	target.draw(fPoint[1], 2, sf::Lines, states);
}