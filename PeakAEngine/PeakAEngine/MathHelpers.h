#pragma once
#include <cstdlib>

float RandomFloat(float min, float max)
{
	const float random = ((float)rand()) / (float)RAND_MAX;
	const float diff = max - min;
	const float r = random * diff;
	return min + r;
}