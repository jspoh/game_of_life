// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <iostream>

#include "mesh.h"
#include "config.h"
#include "utils.h"
#include "render.h"
#include "game.h"


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
	
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, true, NULL);

	// Initialization of your own variables go here
	s8 pFont = AEGfxCreateFont("Assets/liberation-mono.ttf", 72);

	// Changing the window title
	AESysSetWindowTitle("Game of life");

	// reset the system modules
	AESysReset();


	AEGfxVertexList* pMesh = initMesh();
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/border.png");


	bool isPaused = true;
	int frames{ 0 };
	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();


		// Your own update logic goes here
		if (AEInputCheckTriggered(AEVK_SPACE)) {
			isPaused = !isPaused;
			std::cout << "Game paused: " << isPaused << "\n";
		}

		if (!isPaused) {
			frames++;
			if (frames == SIM_SPEED) {
				frames = 0;
				runSim();
			}
		}
		else {
			if (AEInputCheckTriggered(AEVK_LBUTTON)) {
				s32 mouseX, mouseY;
				AEInputGetCursorPosition(&mouseX, &mouseY);
				Grid cell = getSelectedGrid(mouseX, mouseY);
				std::cout << "Mouse clicked at position " << mouseX << ", " << mouseY << " | row: " << cell.row << " col: " << cell.col << "\n";

				rbuf[cell.row][cell.col] = GOL_ALIVE;
				dbuf[cell.row][cell.col] = GOL_ALIVE;
			}
		}

		// Your own rendering logic goes here
		renderGame(pMesh);
		if (isPaused) {
			renderPause(pFont, pTex, pMesh);
		}


		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist()) {
			gGameRunning = 0;
		}
	}

	AEGfxMeshFree(pMesh);
	AEGfxDestroyFont(pFont);
	AEGfxTextureUnload(pTex);
	// free the system
	AESysExit();
}