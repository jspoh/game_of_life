// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <iostream>

#include "mesh.h"
#include "config.h"
#include "utils.h"


// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("Game of life");

	// reset the system modules
	AESysReset();


	AEGfxVertexList* pMesh = initMesh();


	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();


		// Your own update logic goes here


		// Your own rendering logic goes here
		AEGfxSetBackgroundColor(0x0, 0x0, 0x0);
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);

		//AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
		//AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetTransparency(1.0f);

		f32 sX = 0;  // will be overridden later
		f32 sY = - VERTICAL_SEP - GRID_HEIGHT / 2 ;

		//std::cout << stow(0, 0).x << " | " << stow(0, 0).y << "\n";

		for (int i{ 0 }; i < NUM_ROWS; i++) {
			sX = HORIZONTAL_SEP + GRID_WIDTH / 2;
			for (int j{ 0 }; j < NUM_COLS; j++) {
				Pos trans = stow(sX, sY);
				AEMtx33 transform = getTransform(GRID_WIDTH, GRID_HEIGHT, trans.x, trans.y);
				AEGfxSetTransform(transform.m);
				AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

				// update screen pos for grid rendering
				sX += GRID_WIDTH + SEP_DIST;
			}
			sY -= GRID_HEIGHT + SEP_DIST;
		}
		//std::cout << NUM_COLS << " " << NUM_ROWS << "\n";


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}


	// free the system
	AESysExit();
}