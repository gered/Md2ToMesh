#ifndef __CHUNKS_CHUNKS_H_INCLUDED__
#define __CHUNKS_CHUNKS_H_INCLUDED__

#include "../common.h"
#include <stdio.h>

void WriteFileHeader(FILE *fp);

// to be perfectly honest, i don't care to come up with a really elegant solution for this converter tool :p

#include "texcoords.h"
#include "keyframes.h"
#include "keyframetriangles.h"
#include "animations.h"

void WriteChunk(TexCoordsChunk *chunk, FILE *fp);
void WriteChunk(KeyFramesChunk *chunk, FILE *fp);
void WriteChunk(KeyFrameTrianglesChunk *chunk, FILE *fp);
void WriteChunk(AnimationsChunk *chunk, FILE *fp);

#endif
