#ifndef __CHUNKS_TRIANGLES_H_INCLUDED__
#define __CHUNKS_TRIANGLES_H_INCLUDED__

#include "../common.h"
#include "../geometry/triangle.h"

struct TrianglesChunk
{
	static const char *ident = "TRI";

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
};

#endif
