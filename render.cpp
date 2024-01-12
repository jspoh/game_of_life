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

void renderPause(s8 pFont, AEGfxTexture* pTex, AEGfxVertexList* pMesh) {
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 1600, 900);
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, PI*2);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 0, 0);

	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);



	// Tell the Alpha Engine to get ready to draw something with texture.
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Set the the color to multiply to white, so that the sprite can
	// display the full range of colors (default is black).
	AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

	// Set the color to add to nothing, so that we don't alter the sprite's color
	AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);

	// Set blend mode to AE_GFX_BM_BLEND, which will allow transparency.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(0.5f);

	// Tell Alpha Engine to use the texture stored in pTex
	AEGfxTextureSet(pTex, 0, 0);

	// Tell Alpha Engine to use the matrix in 'transform' to apply onto all
	// the vertices of the mesh that we are about to choose to draw in the next line.
	AEGfxSetTransform(transform.m);

	// Tell Alpha Engine to draw the mesh with the above settings.
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

	/* text */
	const char* pText = "PAUSED";
	f32 width, height;
	AEGfxGetPrintSize(pFont, pText, 1.f, &width, &height);
	AEGfxPrint(pFont, pText, -width / 2, -height / 2, 1, 1, 1, 1, 1);
}
