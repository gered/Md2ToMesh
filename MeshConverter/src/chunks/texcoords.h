#ifndef __CHUNKS_TEXCOORDS_H_INCLUDED__
#define __CHUNKS_TEXCOORDS_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector2.h"

struct TexCoordsChunk
{
	static const char *ident = "TXT";

	uint32_t count;
	Vector2 *texCoords;

	TexCoordsChunk()
	{
		count = 0;
		texCoords = NULL;
	}

	~TexCoordsChunk()
	{
		SAFE_DELETE_ARRAY(texCoords);
	}
};

#endif