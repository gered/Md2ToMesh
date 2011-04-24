#ifndef __GEOMETRY_TRIANGLE_H_INCLUDED__
#define __GEOMETRY_TRIANGLE_H_INCLUDED__

#include "../common.h"

class Triangle
{
public:
	uint32_t vertices[3];
	uint32_t normals[3];
	uint32_t texCoords[3];
	uint32_t materialIndex;
};

#endif
