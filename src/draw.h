#pragma once

#include <vector>

struct color
{
	unsigned char R = 256, G = 0, B = 0, A = 0;
};


struct vec3
{
	float x, y, z;
};

struct triangle
{
	vec3 p[3];
};

struct mesh
{
	std::vector<triangle> tris;
};