#pragma once
class MapGrid {
	static int fGridSize;
public:
	/*
		Rounding formula:
		x - input
		y - output
		q - grid size
		r - input % (grid size)

		y = x - r + (r / (0.5q))
	*/
	static int roundToGrid(float pos);
};