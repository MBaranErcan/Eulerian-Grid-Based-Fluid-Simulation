#pragma once

class Physics
{
private:
	// Linear solver: Gauss-Seidel relaxation
	void LinSolve(int b, float* x, float* x0, float a, float c, int iter, int N);

	// Set boundary conditions
	void SetBoundary(int b, float* x, int N);

public:
	Physics();
	~Physics();

	void Diffuse(int b, float* x, float* x0, float diff, float dt, int iter, int N);
	void Advect(int b, float* d, float* d0, float* u, float* v, float dt, int N);
	void Project(float* u, float* v, float* p, float* div, int iter, int N);
};