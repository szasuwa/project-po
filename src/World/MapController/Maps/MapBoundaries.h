#pragma once


struct MapBoundaries {
	bool hasLeft = false;
	bool hasRight = false;
	bool hasTop = false;
	bool hasBottom = false;
	float left = 0;
	float right = 0;
	float top = 0;
	float bottom = 0;

	MapBoundaries & operator=(const MapBoundaries & o) {
		hasLeft = o.hasLeft;
		hasRight = o.hasRight;
		hasTop = o.hasTop;
		hasBottom = o.hasBottom;
		left = o.left;
		right = o.right;
		top = o.top;
		bottom = o.bottom;
		return *this;
	}
};


