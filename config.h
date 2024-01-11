#pragma once


#define GOL_GRID_COLS 30
#define GOL_GRID_ROWS 30
#define GOL_GRID_BUFFERS 2
#define GOL_ALIVE 1
#define GOL_DEAD 0



typedef struct _size {
	float width;
	float height;
} Size;

typedef struct _pos {
	float x;
	float y;
} Pos;

extern Size WINDOW_SIZE;

#define GRID_HEIGHT (WINDOW_SIZE.height / GOL_GRID_COLS)
#define GRID_WIDTH GRID_HEIGHT  //(WINDOW_SIZE.width / GOL_GRID_ROWS)

#define NUM_COLS (WINDOW_SIZE.height / GRID_HEIGHT)
#define NUM_ROWS (WINDOW_SIZE.width / GRID_WIDTH)
