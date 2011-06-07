#ifndef __CHUNKS_KEYFRAMES_H_INCLUDED__
#define __CHUNKS_KEYFRAMES_H_INCLUDED__

#include "../common.h"
#include "../geometry/keyframe.h"
#include <vector>

struct KeyFramesChunk
{
	std::vector<KeyFrame*> frames;
	uint32_t numVertices;

	KeyFramesChunk()
	{
		numVertices = 0;
	}

	~KeyFramesChunk()
	{
		for (uint32_t i = 0; i < frames.size(); ++i)
			SAFE_DELETE(frames[i]);
	}

	KeyFrame* AddFrame()
	{
		KeyFrame *newFrame = new KeyFrame(numVertices);
		frames.push_back(newFrame);
		return newFrame;
	}

	uint32_t GetNumFrames()
	{
		return frames.size();
	}

	uint32_t GetSize()
	{
		if (frames.size() == 0)
			return 0;

		uint32_t size = 4;  // count
		for (uint32_t i = 0; i < frames.size(); ++i)
		{
			size +=
				(
					(sizeof(float) * 3)      // vertex
					+ (sizeof(float) * 3)    // normal
				) * frames[i]->count;
		}

		return size;
	}
};

#endif
