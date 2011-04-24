#ifndef __CHUNK_MATERIALS_H_INCLUDED__
#define __CHUNK_MATERIALS_H_INCLUDED__

#include "../common.h"
#include "../assets/material.h"

struct MaterialsChunk
{
	static const char *ident = "MTL";
	
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
};

#endif
