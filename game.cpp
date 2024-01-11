#include "game.h"
#include "utils.h"


int rbuf[MAX][MAX] = { 0 };  // read buffer
int dbuf[MAX][MAX] = { 0 };  // display buffer

/* copies dbuf into rbuf */
void _deepcopy(void) {
	for (int i{ 0 }; i < MAX; i++) {
		for (int j{ 0 }; j < MAX; j++) {
			rbuf[i][j] = dbuf[i][j];
		}
	}
}

int _getNeighbourCount(int row, int col) {
	int counter = 0;

	for (int i{ -1 }; i < 2; i++) {
		for (int j{ -1 }; j < 2; j++) {
			if (rbuf[row + i][col + j] == GOL_ALIVE) {
				counter++;
			}
		}
	}

	return counter;
}

/* matrix is expanded by 2 dimensions to skip boundary checking */
void runSim(void) {
	for (int i{ 1 }; i < NUM_ROWS + 1; i++) {
		for (int j{ 1 }; j < NUM_COLS + 1; j++) {
			int neighbours = _getNeighbourCount(i, j);

			if (rbuf[i][j] == GOL_ALIVE && (neighbours < 2 || neighbours >3)) {
				dbuf[i][j] = GOL_DEAD;
			}
			else if (rbuf[i][j] == GOL_DEAD && neighbours == 3) {
				dbuf[i][j] = GOL_ALIVE;
			}
		}
	}
	_deepcopy();
}
