#include "MapGrid.h"
int MapGrid::fGridSize = 5;

int MapGrid::roundToGrid(float pos) {
	int mod = int(pos) % fGridSize;
	return pos - mod + fGridSize * ((int)(2 * mod / fGridSize));
}