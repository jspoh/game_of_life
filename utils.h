#pragma once

#include "config.h"
#include "AEEngine.h"


/* world coordinates to screen coordinates */
Pos wtos(float x, float y);

/* screen coordinates to world coordinates */
Pos stow(float x, float y);

/* get grid clicked */
Grid getSelectedGrid(f32 mouseX, f32 mouseY);
