#pragma once
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "../../Frame/Frame.h"
#include "MapBoundaries.h"


class MapGrid : public sf::Drawable, public sf::Transformable {
	static int fGridSize;
	static int fDisplayGridSize;

	sf::VertexArray fHorizontalLines;
	sf::VertexArray fVerticalLines;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	MapGrid();

	void update(const MapBoundaries & map);

	/*
		Rounding formula:
		x - input
		y - output
		q - grid size
		r - input % (grid size)

		y = x - r + (r / (0.5q))
	*/
	static float roundToGrid(float pos);
};