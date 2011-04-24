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
};

#endif
