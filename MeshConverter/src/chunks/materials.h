#ifndef __CHUNK_MATERIALS_H_INCLUDED__
#define __CHUNK_MATERIALS_H_INCLUDED__

#include "../common.h"
#include "../assets/material.h"
#include <vector>

struct MaterialsChunk
{
	std::vector<Material> materials;

	uint32_t GetCount()
	{
		return materials.size();
	}

	uint32_t GetSize()
	{
		if (materials.size() == 0)
			return 0;

		uint32_t size = 4;  // count
		for (uint32_t i = 0; i < materials.size(); ++i)
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
