#ifndef __CHUNKS_KEYFRAMES_H_INCLUDED__
#define __CHUNKS_KEYFRAMES_H_INCLUDED__

#include "../common.h"
#include "../geometry/keyframe.h"
#include <vector>

struct KeyFramesChunk
{
	std::vector<KeyFrame> frames;

	uint32_t GetCount()
	{
		return frames.size();
	}

	uint32_t GetSize()
	{
		if (frames.size() == 0)
			return 0;

		uint32_t size = sizeof(uint32_t);
		size += 
			(
				(sizeof(float) * 3)      // vertex
				+ (sizeof(float) * 3)    // normal
			) * frames.size();

		return size;
	}
};

#endif
