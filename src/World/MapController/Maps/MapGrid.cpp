#include "MapGrid.h"

int MapGrid::fGridSize = 5;
int MapGrid::fDisplayGridSize = 2*fGridSize;


void MapGrid::update(const MapBoundaries & map) {
	float w = map.right - map.left, h = map.bottom - map.top;

	fHorizontalLines = sf::VertexArray(sf::Lines, (h / fDisplayGridSize) * 2);
	int x = map.left;
	int y = map.top;
	int width = fDisplayGridSize + w;

	for (int i = 0; i < fHorizontalLines.getVertexCount(); i += 2) {
		fHorizontalLines[i].position = sf::Vector2f(x, y);
		fHorizontalLines[i].color = GRID_COLOR;


		fHorizontalLines[i + 1].position = sf::Vector2f(width, y);
		fHorizontalLines[i + 1].color = GRID_COLOR;

		y += fDisplayGridSize;
	}

	fVerticalLines = sf::VertexArray(sf::Lines, (w / fDisplayGridSize) * 2);
	int height = fDisplayGridSize + h;
	x = map.left;
	y = map.top;

	for (int i = 0; i < fVerticalLines.getVertexCount(); i += 2) {
		fVerticalLines[i].position = sf::Vector2f(x, y);
		fVerticalLines[i].color = GRID_COLOR;

		fVerticalLines[i+1].position = sf::Vector2f(x, height);
		fVerticalLines[i+1].color = GRID_COLOR;
		x += fDisplayGridSize;
	}
}

void MapGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the entity's transform -- combine it with the one that was passed by the caller
	states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

	// you may also override states.shader or states.blendMode if you want

	// draw the vertex array
	target.draw(fHorizontalLines, states);
	target.draw(fVerticalLines, states);
}

float MapGrid::roundToGrid(float pos) {
	int mod = int(pos) % fGridSize;
	return pos - mod + fGridSize * ((int)(2 * mod / fGridSize));
}

int MapGrid::getGridSize()
{
	return fGridSize;
}

int MapGrid::getGridDisplaySize()
{
	return fDisplayGridSize;
}
