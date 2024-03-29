#include "AEEngine.h"
#include "config.h"


AEGfxVertexList* initMesh(void) {
	AEGfxVertexList* pMesh = NULL;  // already dynamically allocated in AE

	AEGfxMeshStart();

	// square
	AEGfxTriAdd(
		-0.5, 0.5, GRID_COLOR, 0, 0,  // top left
		-0.5, -0.5, GRID_COLOR, 0, 0,  // bottom left
		0.5, -0.5, GRID_COLOR, 0, 0  // bottom right
	);
	AEGfxTriAdd(
		-0.5, 0.5, GRID_COLOR, 0, 0,  // top left
		0.5, 0.5, GRID_COLOR, 0, 0,  // top right
		0.5, -0.5, GRID_COLOR, 0, 0  // bottom right
	);

	pMesh = AEGfxMeshEnd();

	return pMesh;
}


AEMtx33 getTransform(f32 width, f32 height, f32 transX, f32 transY) {
	// Create a scale matrix that scales by 500 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, width, height);

	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, transX, transY);

	// Concatenate the matrices into the 'transform' variable.
	// We concatenate in the order of translation * rotation * scale
	// i.e. this means we scale, then rotate, then translate.
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	return transform;
}
