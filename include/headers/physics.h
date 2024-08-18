#pragma once

#include "headers/Constants.h"

#include <vector>

class Physics
{
public:
	Physics();
	~Physics();

	static float dens[SIZE], dens_prev[SIZE], s[SIZE];
	static float u[SIZE], v[SIZE], u_prev[SIZE], v_prev[SIZE];


	void diffuse(int N, int b, float* x, float* x0, float diff, int ITERS, float dt);
	void advect(int N, int b, float* d, float* d0, float* u, float* v, float dt);
	void project(int N, float* u, float* v, float* p, float* div);

	void set_bnd(int N, int b, float* x);

	void step(float dt);
	void dens_step(int N, float* x, float* x0, float* u, float* v, float diff, int ITERS, float dt);
	void vel_step(int N, float* u, float* v, float* u0, float* v0, float visc, float dt);

	void add_source(int N, float* x, float* s, float dt);
	void reset();
};