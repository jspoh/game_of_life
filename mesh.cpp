#include "AEEngine.h"


AEGfxVertexList* initMesh(void) {
	AEGfxVertexList* pMesh = NULL;  // already dynamically allocated in AE

	AEGfxMeshStart();

	// square
	AEGfxTriAdd(
		-0.5, 0.5, 0xFFFF0000, 0, 0,  // top left
		-0.5, -0.5, 0xFFFF0000, 0, 0,  // bottom left
		0.5, -0.5, 0xFFFF0000, 0, 0  // bottom right
	);
	AEGfxTriAdd(
		-0.5, 0.5, 0xFFFF0000, 0, 0,  // top left
		0.5, 0.5, 0xFFFF0000, 0, 0,  // top right
		0.5, -0.5, 0xFFFF0000, 0, 0  // bottom right
	);

	pMesh = AEGfxMeshEnd();

	return pMesh;
}


AEMtx33 getTransform(void) {
	// Create a scale matrix that scales by 500 x and y
	AEMtx33 scale = { 0 };
	AEMtx33Scale(&scale, 500.f, 500.f);

	// Create a rotation matrix that rotates by 90 degrees
	// Note that PI in radians is 180 degrees.
	// Since 90 degrees is 180/2, 90 degrees in radians is PI/2
	AEMtx33 rotate = { 0 };
	AEMtx33Rot(&rotate, 0);

	// Create a translation matrix that translates by
	// 200 in the x-axis and 100 in the y-axis
	AEMtx33 translate = { 0 };
	AEMtx33Trans(&translate, 0, 0);

	// Concatenate the matrices into the 'transform' variable.
	// We concatenate in the order of translation * rotation * scale
	// i.e. this means we scale, then rotate, then translate.
	AEMtx33 transform = { 0 };
	AEMtx33Concat(&transform, &rotate, &scale);
	AEMtx33Concat(&transform, &translate, &transform);

	return transform;
}
