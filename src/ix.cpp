#include "headers/ix.h"

int IX(int x, int y, int N)
{
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= N) x = N - 1;
	if (y >= N) y = N - 1;

	return x + (y * N);
}