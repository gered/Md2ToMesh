#include "chunks.h"

void WriteFileHeader(FILE *fp)
{
	fputs("MESH", fp);
	uint8_t version = 1;
	fwrite(&version, 1, 1, fp);
}

void WriteChunk(TexCoordsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("TXT", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		fwrite(&chunk->texCoords[i].x, sizeof(float), 1, fp);
		fwrite(&chunk->texCoords[i].y, sizeof(float), 1, fp);
	}
}

void WriteChunk(KeyFramesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("KFR", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t numFrames = chunk->GetNumFrames();
	fwrite(&numFrames, sizeof(uint32_t), 1, fp);
	fwrite(&chunk->numVertices, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < numFrames; ++i)
	{
		KeyFrame *f = chunk->frames[i];

		for (uint32_t j = 0; j < chunk->numVertices; ++j)
		{
			fwrite(&f->vertices[j].x, sizeof(float), 1, fp);
			fwrite(&f->vertices[j].y, sizeof(float), 1, fp);
			fwrite(&f->vertices[j].z, sizeof(float), 1, fp);
		}

		for (uint32_t j = 0; j < chunk->numVertices; ++j)
		{
			fwrite(&f->normals[j].x, sizeof(float), 1, fp);
			fwrite(&f->normals[j].y, sizeof(float), 1, fp);
			fwrite(&f->normals[j].z, sizeof(float), 1, fp);
		}
	}
}

void WriteChunk(KeyFrameTrianglesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("KTR", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		KeyFrameTriangle *t = &chunk->triangles[i];

		fwrite(&t->vertices[0], sizeof(uint32_t), 1, fp);
		fwrite(&t->vertices[1], sizeof(uint32_t), 1, fp);
		fwrite(&t->vertices[2], sizeof(uint32_t), 1, fp);

		fwrite(&t->texCoords[0], sizeof(uint32_t), 1, fp);
		fwrite(&t->texCoords[1], sizeof(uint32_t), 1, fp);
		fwrite(&t->texCoords[2], sizeof(uint32_t), 1, fp);
	}
}

void WriteChunk(AnimationsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("ANI", fp);
	fwrite(&size, sizeof(uint32_t), 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, sizeof(uint32_t), 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		AnimationSequence *a = &chunk->animations[i];

		fwrite(a->name.c_str(), a->name.length(), 1, fp);
		char ch = '\0';
		fwrite(&ch, 1, 1, fp);

		fwrite(&a->start, 4, 1, fp);
		fwrite(&a->end, 4, 1, fp);
	}
}

