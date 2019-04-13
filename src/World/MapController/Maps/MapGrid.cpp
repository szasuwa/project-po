#include "MapGrid.h"
#include <iostream>
int MapGrid::fGridSize = 5;
int MapGrid::fDisplayGridSize = 2*fGridSize;

int MapGrid::roundToGrid(float pos) {
	int mod = int(pos) % fGridSize;
	return pos - mod + fGridSize * ((int)(2 * mod / fGridSize));
}

MapGrid::MapGrid(){

}

void MapGrid::update() {
	sf::Color gridColor = sf::Color(200, 200, 200, 100);
	Frame & frame = Frame::getInstance();
	float w = frame.getFrameWidth(), h = frame.getFrameHeight();

	fHorizontalLines = sf::VertexArray(sf::Lines, (h / fDisplayGridSize) * 2 + 2 * 4);
	int x = -2 * fDisplayGridSize;
	int y = x;
	int width = 2 * fDisplayGridSize + w;

	for (int i = 0; i < fHorizontalLines.getVertexCount(); i += 2) {
		fHorizontalLines[i].position = sf::Vector2f(x, y);
		fHorizontalLines[i].color = gridColor;


		fHorizontalLines[i + 1].position = sf::Vector2f(width, y);
		fHorizontalLines[i + 1].color = gridColor;

		y += fDisplayGridSize;
	}

	fVerticalLines = sf::VertexArray(sf::Lines, (w / fDisplayGridSize) * 2 + 2 * 4);
	int height = 2 * fDisplayGridSize + h;
	y = x;

	for (int i = 0; i < fVerticalLines.getVertexCount(); i += 2) {
		fVerticalLines[i].position = sf::Vector2f(x, y);
		fVerticalLines[i].color = gridColor;

		fVerticalLines[i+1].position = sf::Vector2f(x, height);
		fVerticalLines[i+1].color = gridColor;
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

void MapGrid::setOrigin(sf::Vector2f o)
{
	while (o.x > fDisplayGridSize) {
		o.x -= fDisplayGridSize;
	}

	while (o.x < -fDisplayGridSize) {
		o.x += fDisplayGridSize;
	}

	while (o.y > fDisplayGridSize) {
		o.y -= fDisplayGridSize;
	}

	while (o.y < -fDisplayGridSize) {
		o.y += fDisplayGridSize;
	}

	Transformable::setOrigin(o);
}