#ifndef __CHUNKS_NORMALS_H_INCLUDED__
#define __CHUNKS_NORMALS_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector3.h"
#include <vector>

struct NormalsChunk
{
	std::vector<Vector3> normals;

	uint32_t GetCount()
	{
		return normals.size();
	}

	uint32_t GetSize()
	{
		if (normals.size() == 0)
			return 0;

		uint32_t size = 4;  // count
		size += 
			(sizeof(float) * 3)   // x, y, z
			* normals.size();

		return size;
	}
};

#endif
