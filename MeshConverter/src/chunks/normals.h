#ifndef __CHUNKS_NORMALS_H_INCLUDED__
#define __CHUNKS_NORMALS_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector3.h"

struct NormalsChunk
{
	static const char *ident = "NRL";

	uint32_t count;
	Vector3 *normals;

	NormalsChunk()
	{
		count = 0;
		normals = NULL;
	}

	~NormalsChunk()
	{
		SAFE_DELETE_ARRAY(normals);
	}

	size_t GetSize()
	{
		if (count == 0)
			return 0;

		size_t size = sizeof(uint32_t);
		size += 
			(sizeof(float) * 3)   // x, y, z
			* count;

		return size;
	}
};

#endif
