#ifndef __CHUNKS_TRIANGLES_H_INCLUDED__
#define __CHUNKS_TRIANGLES_H_INCLUDED__

#include "../common.h"
#include "../geometry/triangle.h"
#include <vector>

struct TrianglesChunk
{
	std::vector<Triangle> triangles;

	uint32_t GetCount()
	{
		return triangles.size();
	}

	uint32_t GetSize()
	{
		if (triangles.size() == 0)
			return 0;

		uint32_t size = 4;  // count
		size += 
			(
				(4 * 3)   // vertex indices
				+ (4 * 3) // normal indices
				+ (4 * 3) // texcoord indices
				+ 4       // material index
			) * triangles.size();

		return size;
	}
};

#endif
