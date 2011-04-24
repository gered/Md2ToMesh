#ifndef __CHUNKS_CHUNKS_H_INCLUDED__
#define __CHUNKS_CHUNKS_H_INCLUDED__

#include "../common.h"
#include <stdio.h>

void WriteFileHeader(FILE *fp);

// to be perfectly honest, i don't care to come up with a really elegant solution for this converter tool :p

#include "vertices.h"
#include "normals.h"
#include "texcoords.h"
#include "materials.h"
#include "triangles.h"

void WriteChunk(VerticesChunk *chunk, FILE *fp);
void WriteChunk(NormalsChunk *chunk, FILE *fp);
void WriteChunk(TexCoordsChunk *chunk, FILE *fp);
void WriteChunk(MaterialsChunk *chunk, FILE *fp);
void WriteChunk(TrianglesChunk *chunk, FILE *fp);

#endif
