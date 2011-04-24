#ifndef __CHUNKS_VERTICES_H_INCLUDED__
#define __CHUNKS_VERTICES_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector3.h"

struct VerticesChunk
{
	static const char *ident = "VTX";

	uint32_t count;
	Vector3 *vertices;

	VerticesChunk()
	{
		count = 0;
		vertices = NULL;
	}

	~VerticesChunk()
	{
		SAFE_DELETE_ARRAY(vertices);
	}
};

#endif
