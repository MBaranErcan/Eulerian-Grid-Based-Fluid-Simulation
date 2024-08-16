#pragma once
const int ITERS = 20;

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// Grid dimensions
const int N = 7;				// Grid resolution
const int SIZE = (N+2) * (N+2);	// Grid size
const float h = 1.0f / SIZE;			// Grid spacing


// Macros
#define IX(i, j)	((i) + (SIZE + 2) * (j))
#define SWAP(x0, x)	{float * tmp = x0; x0 = x; x = tmp;}