#ifndef __CHUNKS_VERTICES_H_INCLUDED__
#define __CHUNKS_VERTICES_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector3.h"
#include <vector>

struct VerticesChunk
{
	std::vector<Vector3> vertices;

	uint32_t GetCount()
	{
		return vertices.size();
	}

	uint32_t GetSize()
	{
		if (vertices.size() == 0)
			return 0;

		uint32_t size = 4;  // count
		size += 
			(sizeof(float) * 3)   // x, y, z
			* vertices.size();

		return size;
	}
};

#endif
