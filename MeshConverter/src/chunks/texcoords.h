#ifndef __CHUNKS_TEXCOORDS_H_INCLUDED__
#define __CHUNKS_TEXCOORDS_H_INCLUDED__

#include "../common.h"
#include "../geometry/vector2.h"
#include <vector>

struct TexCoordsChunk
{
	std::vector<Vector2> texCoords;

	uint32_t GetCount()
	{
		return texCoords.size();
	}

	uint32_t GetSize()
	{
		if (texCoords.size() == 0)
			return 0;

		uint32_t size = 4;  // count
		size += 
			(sizeof(float) * 2)   // u, v
			* texCoords.size();

		return size;
	}
};

#endif
