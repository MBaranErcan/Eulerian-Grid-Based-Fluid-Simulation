#pragma once
const int ITERS = 24;

// Screen dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// Grid dimensions
const int N = 128;				// Grid resolution
const int SIZE = (N+2) * (N+2);	// Grid size
const float h = 1.0f / SIZE;			// Grid spacing


// Macros
#define IX(i, j)	((i) + (N + 2) * (j))
#define SWAP(x0, x)	{float * tmp = x0; x0 = x; x = tmp;}

// Physics constants
const float visc = 0.0001f;		// Viscosity
const float diff = 0.0002f;		// Diffusion
const float addDensity = 0.5f;	// Density added per frame
const int	addRadius = 4;		// Radius of density added
const float addForce = 0.1f;	// Force added per frame
const float decay = 0.997f;		// Decay rate for velocity field