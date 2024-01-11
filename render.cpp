#include "render.h"
#include "config.h"
#include "utils.h"
#include <iostream>
#include "mesh.h"
#include "game.h"


void renderGame(AEGfxVertexList* pMesh) {
	AEGfxSetBackgroundColor(0x0, 0x0, 0x0);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);

	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(1.0f);

	f32 sX = 0;  // will be overridden later
	f32 sY = -VERTICAL_SEP - GRID_HEIGHT / 2;

	//std::cout << stow(0, 0).x << " | " << stow(0, 0).y << "\n";

	for (int i{ 1 }; i < NUM_ROWS+1; i++) {
		sX = HORIZONTAL_SEP + GRID_WIDTH / 2;
		for (int j{ 1 }; j < NUM_COLS+1; j++) {
			Pos trans = stow(sX, sY);
			AEMtx33 transform = getTransform(GRID_WIDTH, GRID_HEIGHT, trans.x, trans.y);
			AEGfxSetTransform(transform.m);

			// set color of cell conditionally
			if (dbuf[i][j] == GOL_ALIVE) {
				AEGfxSetColorToAdd(1.f, 0.f, 0.f, 0.0f);
			}
			else {
				AEGfxSetColorToAdd(0.7f, 0.7f, 0.7f, 0.0f);
			}

			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

			// update screen pos for grid rendering
			sX += GRID_WIDTH + SEP_DIST;
		}
		sY -= GRID_HEIGHT + SEP_DIST;
	}
	//std::cout << NUM_COLS << " " << NUM_ROWS << "\n";
}
