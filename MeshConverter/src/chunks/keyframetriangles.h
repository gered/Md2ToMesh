#ifndef __CHUNKS_KEYFRAMETRIANGLES_H_INCLUDED__
#define __CHUNKS_KEYFRAMETRIANGLES_H_INCLUDED__

#include "../common.h"
#include "../geometry/keyframetriangle.h"
#include <vector>

struct KeyFrameTrianglesChunk
{
	std::vector<KeyFrameTriangle> triangles;

	uint32_t GetCount()
	{
		return triangles.size();
	}

	uint32_t GetSize()
	{
		if (triangles.size() == 0)
			return 0;

		uint32_t size = sizeof(uint32_t);
		size += 
			(
				(sizeof(uint32_t) * 3)      // vertex indices
				+ (sizeof(uint32_t) * 3)    // texcoord indices
			) * triangles.size();

		return size;
	}
};

#endif
