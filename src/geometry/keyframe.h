#ifndef __GEOMETRY_KEYFRAME_H_INCLUDED__
#define __GEOMETRY_KEYFRAME_H_INCLUDED__

#include "../common.h"
#include "vector3.h"

class KeyFrame
{
public:
	uint32_t count;
	Vector3 *vertices;
	Vector3 *normals;

	KeyFrame(uint32_t numVertices)
	{
		count = numVertices;
		vertices = new Vector3[count];
		normals = new Vector3[count];
	}

	~KeyFrame()
	{
		SAFE_DELETE_ARRAY(vertices);
		SAFE_DELETE_ARRAY(normals);
	}
};

#endif
