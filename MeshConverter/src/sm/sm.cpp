#include "sm.h"

#include <stdio.h>
#include "../util/files.h"
#include "../chunks/chunks.h"

StaticModel::StaticModel()
{
	m_numMaterials = 0;
	m_numPolygons = 0;
	m_numVertices = 0;
	m_numNormals = 0;
	m_numTexCoords = 0;
	m_hasNormals = false;
	m_hasTexCoords = false;
	m_hasColors = false;
	m_materials = NULL;
	m_polygons = NULL;
	m_texCoords = NULL;
	m_vertices = NULL;
	m_normals = NULL;
}

void StaticModel::Release()
{
	delete[] m_materials;
	delete[] m_polygons;
	delete[] m_texCoords;
	delete[] m_vertices;
	delete[] m_normals;
}

bool StaticModel::Load(const std::string &file)
{
	FILE *fp;
	unsigned short numMaterials;
	unsigned int numPolys, numVertices, numNormals, numTexCoords;
	unsigned int ambient, diffuse, specular, emission;
	unsigned int n;
	int currentMaterial;
	int count;
	float x, y, z;
	unsigned char header[2];
	unsigned char c;
	std::string texture;

	fp = fopen(file.c_str(), "rb");
	if (!fp)
		return false;

	// Simple file type validation
	fread(&header[0], 2, 1, fp);
	if (header[0] != 'S' || header[1] != 'M')
		return false;

	fread(&numMaterials, 2, 1, fp);
	fread(&numPolys, 4, 1, fp);
	fread(&numVertices, 4, 1, fp);
	fread(&numNormals, 4, 1, fp);
	fread(&numTexCoords, 4, 1, fp);

	m_materials = new SmMaterial[numMaterials];
	m_polygons = new SmPolygon[numPolys];
	m_texCoords = new Vector2[numTexCoords];
	m_vertices = new Vector3[numVertices];
	m_normals = new Vector3[numNormals];

	//ASSERT(m_materials != NULL);
	//ASSERT(m_polygons != NULL);
	//ASSERT(m_texCoords != NULL);
	//ASSERT(m_vertices != NULL);
	//ASSERT(m_normals != NULL);

	m_numMaterials = numMaterials;
	m_numPolygons = numPolys;
	m_numVertices = numVertices;
	m_numNormals = numNormals;
	m_numTexCoords = numTexCoords;

	// Read in material definitions
	for (int i = 0; i < m_numMaterials; ++i)
	{
		fread(&ambient, 4, 1, fp);
		fread(&diffuse, 4, 1, fp);
		fread(&specular, 4, 1, fp);
		fread(&emission, 4, 1, fp);

		m_materials[i].material->ambient = Color::FromInt(ambient);
		m_materials[i].material->diffuse = Color::FromInt(diffuse);
		m_materials[i].material->specular = Color::FromInt(specular);
		m_materials[i].material->emissive = Color::FromInt(emission);
		m_materials[i].material->shininess = 0.0f;
		m_materials[i].material->opacity = COLOR_ALPHA_OPAQUE;
		ReadString(fp, m_materials[i].material->name);
	}

	// Read in triangle definitions (all are indexes into raw data following)
	currentMaterial = NO_MATERIAL;
	for (unsigned int i = 0; i < m_numPolygons; ++i)
	{
		// Vertices
		for (int j = 0; j < 3; ++j)
		{
			fread(&n, 4, 1, fp);
			m_polygons[i].vertices[j] = n;
		}

		// Normals
		for (int j = 0; j < 3; ++j)
		{
			fread(&n, 4, 1, fp);
			m_polygons[i].normals[j] = n;
		}

		// TexCoords
		for (int j = 0; j < 3; ++j)
		{
			fread(&n, 4, 1, fp);
			m_polygons[i].texcoords[j] = n;
		}
		
		// Vertex colors
		for (int j = 0; j < 3; ++j)
		{
			fread(&n, 2, 1, fp);
			m_polygons[i].colors[j] = n;
		}

		// Material index
		fread(&m_polygons[i].material, 2, 1, fp);

		// Record start/end indices for the different materials
		// This way rendering can be done per material while still only looping
		// over all of this model's polygons once per frame
		if (m_polygons[i].material != currentMaterial)
		{
			if (currentMaterial > NO_MATERIAL)
				m_materials[currentMaterial].polyEnd = i;

			currentMaterial = m_polygons[i].material;
			m_materials[currentMaterial].polyStart = i;
		}

		// If any of the normals, texcoords, or colors are non-zero, we need to flag that such
		// information exists in this model
		if (m_polygons[i].colors[0] != 0 || m_polygons[i].colors[1] != 0 || m_polygons[i].colors[2] != 0)
			m_hasColors = true;
	}

	// Will always include the last polygon due to the way the .SM exporter sorts
	m_materials[currentMaterial].polyEnd = numPolys;

	// Vertices
	for (unsigned int i = 0; i < m_numVertices; ++i)
	{
		fread(&x, 4, 1, fp);
		fread(&y, 4, 1, fp);
		fread(&z, 4, 1, fp);

		m_vertices[i].x = x / 2;
		m_vertices[i].y = y / 2;
		m_vertices[i].z = z / 2;
	}

	// Normals
	for (unsigned int i = 0; i < m_numNormals; ++i)
	{
		fread(&x, 4, 1, fp);
		fread(&y, 4, 1, fp);
		fread(&z, 4, 1, fp);
		//ASSERT(!((x >= 1.0f || x <= -1.0f) ||
		//	(y >= 1.0f || y <= -1.0f) ||
		//	(z >= 1.0f || z <= -1.0f)));
		m_normals[i].x = x;
		m_normals[i].y = y;
		m_normals[i].z = z;

		if (m_normals[i].x != 0 || m_normals[i].y != 0 || m_normals[i].z != 0)
			m_hasNormals = true;
	}

	// Texture coordinates
	for (unsigned int i = 0; i < m_numTexCoords; ++i)
	{
		fread(&x, 4, 1, fp);
		fread(&y, 4, 1, fp);
		//ASSERT(!((x >= 2048.0f || x <= -2048.0f) ||
		//	(y >= 2048.0f || y <= -2048.0f)));

		// TODO: revisit this, seems a bit hack-ish and probably only correct 
		// for the shitty models I made
		m_texCoords[i].x = x;
		m_texCoords[i].y = -y;

		if (m_texCoords[i].x != 0 || m_texCoords[i].y != 0)
			m_hasTexCoords = true;
	}

	fclose(fp);

	return true;
}

bool StaticModel::ConvertToMesh(const std::string &file)
{
	FILE *fp = fopen(file.c_str(), "wb");
	if (fp == NULL)
		return false;

	WriteFileHeader(fp);

	VerticesChunk *verticesChunk = new VerticesChunk();
	for (long i = 0; i < m_numVertices; ++i)
		verticesChunk->vertices.push_back(m_vertices[i]);
	WriteChunk(verticesChunk, fp);
	SAFE_DELETE(verticesChunk);

	NormalsChunk *normalsChunk = new NormalsChunk();
	for (long i = 0; i < m_numNormals; ++i)
		normalsChunk->normals.push_back(m_normals[i]);
	WriteChunk(normalsChunk, fp);
	SAFE_DELETE(normalsChunk);

	TexCoordsChunk *texCoordsChunk = new TexCoordsChunk();
	for (long i = 0; i < m_numTexCoords; ++i)
		texCoordsChunk->texCoords.push_back(m_texCoords[i]);
	WriteChunk(texCoordsChunk, fp);
	SAFE_DELETE(texCoordsChunk);

	MaterialsChunk *materialsChunk = new MaterialsChunk();
	for (long i = 0; i < m_numMaterials; ++i)
		materialsChunk->materials.push_back(*m_materials[i].material);
	WriteChunk(materialsChunk, fp);
	SAFE_DELETE(materialsChunk);

	TrianglesChunk *trianglesChunk = new TrianglesChunk();
	for (long i = 0; i < m_numPolygons; ++i)
	{
		Triangle t;

		t.vertices[0] = m_polygons[i].vertices[0];
		t.vertices[1] = m_polygons[i].vertices[1];
		t.vertices[2] = m_polygons[i].vertices[2];

		t.normals[0] = m_polygons[i].normals[0];
		t.normals[1] = m_polygons[i].normals[1];
		t.normals[2] = m_polygons[i].normals[2];

		t.texCoords[0] = m_polygons[i].texcoords[0];
		t.texCoords[1] = m_polygons[i].texcoords[1];
		t.texCoords[2] = m_polygons[i].texcoords[2];

		t.materialIndex = m_polygons[i].material;

		trianglesChunk->triangles.push_back(t);
	}
	WriteChunk(trianglesChunk, fp);

	fclose(fp);
	return true;
}
