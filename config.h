#pragma once


#define SIM_SPEED 5  // number of frames before an update. bigger number means slower


#define GOL_GRID_COLS 30
#define GOL_GRID_ROWS 30
#define GOL_GRID_BUFFERS 2
#define GOL_ALIVE 1
#define GOL_DEAD 0

#define MAX 100

#define GRID_COLOR 0xFF000000

#define SEP_DIST 5

typedef struct _size {
	float width;
	float height;
} Size;

typedef struct _pos {
	float x;
	float y;
} Pos;

typedef struct _grid {
	int row;
	int col;
} Grid;

extern Size WINDOW_SIZE;

#define GRID_HEIGHT (((WINDOW_SIZE.height - SEP_DIST) / GOL_GRID_COLS) - SEP_DIST)
#define GRID_WIDTH GRID_HEIGHT  //(WINDOW_SIZE.width / GOL_GRID_ROWS)

#define NUM_ROWS trunc((WINDOW_SIZE.height - SEP_DIST) / (GRID_HEIGHT + SEP_DIST))
#define NUM_COLS trunc((WINDOW_SIZE.width - SEP_DIST) / (GRID_WIDTH + SEP_DIST))

#define HORIZONTAL_SEP ((WINDOW_SIZE.width - (NUM_COLS * GRID_WIDTH) - (NUM_COLS-1)*SEP_DIST)/2)
#define VERTICAL_SEP ((WINDOW_SIZE.height - (NUM_ROWS*GRID_HEIGHT) - (NUM_ROWS-1)*SEP_DIST)/2)
