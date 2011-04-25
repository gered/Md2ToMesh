#include "chunks.h"

void WriteFileHeader(FILE *fp)
{
	fputs("MESH", fp);
	uint8_t version = 1;
	fwrite(&version, 1, 1, fp);
}

void WriteChunk(VerticesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("VTX", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		fwrite(&chunk->vertices[i].x, sizeof(float), 1, fp);
		fwrite(&chunk->vertices[i].y, sizeof(float), 1, fp);
		fwrite(&chunk->vertices[i].z, sizeof(float), 1, fp);
	}
}

void WriteChunk(NormalsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("NRL", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		fwrite(&chunk->normals[i].x, sizeof(float), 1, fp);
		fwrite(&chunk->normals[i].y, sizeof(float), 1, fp);
		fwrite(&chunk->normals[i].z, sizeof(float), 1, fp);
	}
}

void WriteChunk(TexCoordsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("TXT", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		fwrite(&chunk->texCoords[i].x, sizeof(float), 1, fp);
		fwrite(&chunk->texCoords[i].y, sizeof(float), 1, fp);
	}
}

void WriteChunk(MaterialsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("MTL", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		Material *m = &chunk->materials[i];

		fwrite(m->name.c_str(), m->name.length(), 1, fp);
		char ch = '\0';
		fwrite(&ch, 1, 1, fp);

		fwrite(&m->ambient.r, sizeof(float), 1, fp);
		fwrite(&m->ambient.g, sizeof(float), 1, fp);
		fwrite(&m->ambient.b, sizeof(float), 1, fp);
		fwrite(&m->ambient.a, sizeof(float), 1, fp);

		fwrite(&m->diffuse.r, sizeof(float), 1, fp);
		fwrite(&m->diffuse.g, sizeof(float), 1, fp);
		fwrite(&m->diffuse.b, sizeof(float), 1, fp);
		fwrite(&m->diffuse.a, sizeof(float), 1, fp);

		fwrite(&m->specular.r, sizeof(float), 1, fp);
		fwrite(&m->specular.g, sizeof(float), 1, fp);
		fwrite(&m->specular.b, sizeof(float), 1, fp);
		fwrite(&m->specular.a, sizeof(float), 1, fp);

		fwrite(&m->emissive.r, sizeof(float), 1, fp);
		fwrite(&m->emissive.g, sizeof(float), 1, fp);
		fwrite(&m->emissive.b, sizeof(float), 1, fp);
		fwrite(&m->emissive.a, sizeof(float), 1, fp);

		fwrite(&m->shininess, sizeof(float), 1, fp);

		fwrite(&m->opacity, sizeof(float), 1, fp);
	}
}

void WriteChunk(TrianglesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("TRI", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		Triangle *t = &chunk->triangles[i];

		fwrite(&t->vertices[0], 4, 1, fp);
		fwrite(&t->vertices[1], 4, 1, fp);
		fwrite(&t->vertices[2], 4, 1, fp);

		fwrite(&t->normals[0], 4, 1, fp);
		fwrite(&t->normals[1], 4, 1, fp);
		fwrite(&t->normals[2], 4, 1, fp);

		fwrite(&t->texCoords[0], 4, 1, fp);
		fwrite(&t->texCoords[1], 4, 1, fp);
		fwrite(&t->texCoords[2], 4, 1, fp);

		fwrite(&t->materialIndex, 4, 1, fp);
	}
}

void WriteChunk(KeyFramesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("KFR", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t numFrames = chunk->GetNumFrames();
	fwrite(&numFrames, 4, 1, fp);
	fwrite(&chunk->numVertices, 4, 1, fp);

	for (uint32_t i = 0; i < numFrames; ++i)
	{
		KeyFrame *f = chunk->frames[i];

		for (uint32_t j = 0; j < chunk->numVertices; ++j)
		{
			fwrite(&f->vertices->x, sizeof(float), 1, fp);
			fwrite(&f->vertices->y, sizeof(float), 1, fp);
			fwrite(&f->vertices->z, sizeof(float), 1, fp);
		}

		for (uint32_t j = 0; j < chunk->numVertices; ++j)
		{
			fwrite(&f->normals->x, sizeof(float), 1, fp);
			fwrite(&f->normals->y, sizeof(float), 1, fp);
			fwrite(&f->normals->z, sizeof(float), 1, fp);
		}
	}
}

void WriteChunk(KeyFrameTrianglesChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("KTR", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

	for (uint32_t i = 0; i < count; ++i)
	{
		KeyFrameTriangle *t = &chunk->triangles[i];

		fwrite(&t->vertices[0], 4, 1, fp);
		fwrite(&t->vertices[1], 4, 1, fp);
		fwrite(&t->vertices[2], 4, 1, fp);

		fwrite(&t->texCoords[0], 4, 1, fp);
		fwrite(&t->texCoords[1], 4, 1, fp);
		fwrite(&t->texCoords[2], 4, 1, fp);
	}
}

void WriteChunk(AnimationsChunk *chunk, FILE *fp)
{
	uint32_t size = chunk->GetSize();
	if (size == 0)
		return;

	fputs("ANI", fp);
	fwrite(&size, 4, 1, fp);
	uint32_t count = chunk->GetCount();
	fwrite(&count, 4, 1, fp);

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
