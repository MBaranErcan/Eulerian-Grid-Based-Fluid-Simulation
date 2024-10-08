#pragma once

#include "headers/Physics.h"

float Physics::u[SIZE] = { 0 };
float Physics::v[SIZE] = { 0 };
float Physics::u_prev[SIZE] = { 0 };
float Physics::v_prev[SIZE] = { 0 };
float Physics::dens[SIZE] = { 0 };
float Physics::dens_prev[SIZE] = { 0 };
float Physics::s[SIZE] = { 0 };

/*--------------------------
  Constructor and Destructor
---------------------------*/

Physics::Physics() {}

Physics::~Physics() {}


/*-----------------------
  Diffuse-Advect-Project
-----------------------*/

// Gauss-Seidel relaxation
void Physics::diffuse (int N, int b, float* x, float* x0, float diff, int ITERS, float dt)
{
	int i, j, k;
	float a = dt * diff * (N * N);

	for (k = 0; k < ITERS; k++) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++)
			{
				x[IX(i, j)] = (x0[IX(i, j)] + a
					* (x[IX(i - 1, j)] + x[IX(i + 1, j)] + x[IX(i, j - 1)] + x[IX(i, j + 1)])) / (1 + (4 * a));
			}
		}
		set_bnd(N, b, x);
	}
}

void Physics::advect(int N, int b, float* d, float* d0, float* u, float* v, float dt)
{
	int i, j, i0, j0, i1, j1;
	float x, y, s0, t0, s1, t1, dt0;

	dt0 = dt * N;

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			x = i - dt0 * u[IX(i, j)]; // x and y represent the new position in the grid
			y = j - dt0 * v[IX(i, j)];

			// i0, i1, j0, j1 are the four corners of the cell
			if (x < 0.5) x = 0.5;	if (x > N + 0.5) x = N + 0.5;	i0 = (int)x;	i1 = i0 + 1;
			if (y < 0.5) y = 0.5;	if (y > N + 0.5) y = N + 0.5;	j0 = (int)y;	j1 = j0 + 1;

			s1 = x - i0;	s0 = 1 - s1;	t1 = y - j0;	t0 = 1 - t1; // how far are we from the corners

			d[IX(i, j)] = s0 * (t0 * d0[IX(i0, j0)] + t1 * d0[IX(i0, j1)]) +	// Bilinear interpolation
				s1 * (t0 * d0[IX(i1, j0)] + t1 * d0[IX(i1, j1)]);
		}
	}
	set_bnd(N, b, d);
}

void Physics::project(int N, float* u, float* v, float* p, float* div) // p is pressure, div is divergence
{
	int i, j, k;

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			div[IX(i, j)] = -0.5f * h * (u[IX(i + 1, j)] - u[IX(i - 1, j)] + v[IX(i, j + 1)] - v[IX(i, j - 1)]);

			p[IX(i, j)] = 0;
		}
	}
	set_bnd(N, 0, div);	set_bnd(N, 0, p);

	for (k = 0; k < ITERS; k++) {
		for (i = 1; i <= N; i++) {
			for (j = 1; j <= N; j++) {
				p[IX(i, j)] = (div[IX(i, j)] + p[IX(i - 1, j)] + p[IX(i + 1, j)] + p[IX(i, j - 1)] + p[IX(i, j + 1)]) / 4;
			}
		}
		set_bnd(N, 0, p);
	}

	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			u[IX(i, j)] -= 0.5 * (p[IX(i + 1, j)] - p[IX(i - 1, j)]) / h;
			v[IX(i, j)] -= 0.5 * (p[IX(i, j + 1)] - p[IX(i, j - 1)]) / h;
		}
	}
	set_bnd(N, 1, u);	set_bnd(N, 2, v);
}


/*-------------------------------------
Update the fluid (density and velocity)
-------------------------------------*/

void Physics::step(float dt)
{
	vel_step(N, u, v, u_prev, v_prev, visc, dt);
	dens_step(N, dens, dens_prev, u, v, diff, 4, dt);
}

void Physics::dens_step (int N, float* x, float* x0, float* u, float* v, float diff, int ITERS, float dt)
{
	add_source(N, x, s, dt);							// External inputs
	SWAP(x0, x); diffuse(N, 0, x, x0, diff, ITERS, dt);	// Diffusion
	SWAP(x0, x); advect(N, 0, x, x0, u, v, dt);			// Advection
}

// Update velocity field of the fluid
void Physics::vel_step (int N, float* u, float* v, float* u0, float* v0, float visc, float dt)
{
	add_source(N, u, u0, dt); add_source(N, v, v0, dt);	// External inputs
	SWAP(u0, u); diffuse(N, 1, u, u0, visc, 4, dt);		// Diffusion
	SWAP(v0, v); diffuse(N, 2, v, v0, visc, 4, dt);		// Diffusion
	project(N, u, v, u0, v0);							// Projection
	SWAP(u0, u); SWAP(v0, v);
	advect(N, 1, u, u0, u0, v0, dt);					// Advection
	advect(N, 2, v, v0, u0, v0, dt);					// Advection
	project(N, u, v, u0, v0);							// Projection
	for (int i = 0; i < SIZE; i++) {
		u[i] *= decay;
		v[i] *= decay;
	}
}	// we call project twice beacause advect() behaves more accurately when the velocity field is divergence-free

void Physics::reset()
{
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			u[IX(i, j)] = 0;
			v[IX(i, j)] = 0;
			u_prev[IX(i, j)] = 0;
			v_prev[IX(i, j)] = 0;
			dens[IX(i, j)] = 0;
			dens_prev[IX(i, j)] = 0;
			s[IX(i, j)] = 0;
		}
	}
}


// Add user input to the density field
void Physics::add_source(int N, float* x, float* s, float dt)
{
	for (int i = 0; i < SIZE; i++) x[i] += dt * s[i];
}

// Horizontal velocity on vertical walls, vertical velocity on horizontal walls is 0
void Physics::set_bnd(int N, int b, float* x)
{
	int i;

	for (i = 1; i <= N; i++) {
		x[IX(0, i)] = b == 1 ? -x[IX(1, i)] : x[IX(1, i)];
		x[IX(N + 1, i)] = b == 1 ? -x[IX(N, i)] : x[IX(N, i)];
		x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
		x[IX(i, N + 1)] = b == 2 ? -x[IX(i, N)] : x[IX(i, N)];
	}
	// Corners
	x[IX(0, 0)] = 0.5f * (x[IX(1, 0)] + x[IX(0, 1)]);
	x[IX(0, N + 1)] = 0.5f * (x[IX(1, N + 1)] + x[IX(0, N)]);
	x[IX(N + 1, 0)] = 0.5f * (x[IX(N, 0)] + x[IX(N + 1, 1)]);
	x[IX(N + 1, N + 1)] = 0.5f * (x[IX(N, N + 1)] + x[IX(N + 1, N)]);
}
