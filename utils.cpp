#include "utils.h"


/* world coordinates to screen coordinates */
Pos wtos(float x, float y) {
	float sX = (WINDOW_SIZE.width / 2) + x;
	float sY = (WINDOW_SIZE.height / 2) + y;
	return Pos{ sX, sY };
}


/* screen coordinates to world coordinates */
Pos stow(float x, float y) {
	float wX = x - (WINDOW_SIZE.width / 2);
	float wY = y - (WINDOW_SIZE.height / 2);
	return Pos{ wX, wY };
}
