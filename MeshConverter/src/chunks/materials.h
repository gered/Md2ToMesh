#ifndef __CHUNK_MATERIALS_H_INCLUDED__
#define __CHUNK_MATERIALS_H_INCLUDED__

#include "../common.h"
#include "../assets/material.h"

struct MaterialsChunk
{
	uint32_t count;
	Material *materials;

	MaterialsChunk()
	{
		count = 0;
		materials = NULL;
	}

	~MaterialsChunk()
	{
		SAFE_DELETE_ARRAY(materials);
	}

	uint32_t GetSize()
	{
		if (count == 0)
			return 0;

		uint32_t size = sizeof(uint32_t);
		for (uint32_t i = 0; i < count; ++i)
		{
			size += materials[i].name.length() + 1;   // include null terminator
			size += sizeof(float) * 4;  // ambient
			size += sizeof(float) * 4;  // diffuse
			size += sizeof(float) * 4;  // specular
			size += sizeof(float) * 4;  // emissive
			size += sizeof(float);      // shininess
			size += sizeof(float);      // opacity
		}

		return size;
	}
};

#endif
