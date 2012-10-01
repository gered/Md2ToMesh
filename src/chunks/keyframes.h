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
		if (GetNumFrames() == 0)
			return 0;

		uint32_t vertexSize = (sizeof(float) * 3) * 2; // vertex and normal xyz
		uint32_t frameSize = vertexSize * numVertices;

		uint32_t size = sizeof(uint32_t) * 2;  // count of frames & vertices
		size += frameSize * GetNumFrames();

		return size;
	}
};

#endif
