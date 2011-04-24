#ifndef __CHUNKS_TRIANGLES_H_INCLUDED__
#define __CHUNKS_TRIANGLES_H_INCLUDED__

#include "../common.h"
#include "../geometry/triangle.h"

struct TrianglesChunk
{
	uint32_t count;
	Triangle *triangles;

	TrianglesChunk()
	{
		count = 0;
		triangles = NULL;
	}

	~TrianglesChunk()
	{
		SAFE_DELETE_ARRAY(triangles);
	}

	uint32_t GetSize()
	{
		if (count == 0)
			return 0;

		uint32_t size = sizeof(uint32_t);
		size += 
			(
				(sizeof(uint32_t) * 3)   // vertex indices
				+ (sizeof(uint32_t) * 3) // normal indices
				+ (sizeof(uint32_t) * 3) // texcoord indices
				+ sizeof(uint32_t)       // material index
			) * count;

		return size;
	}
};

#endif
