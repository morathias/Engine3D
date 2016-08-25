#ifndef MESH_H
#define MESH_H
//========================================================================================
#define DllExport __declspec( dllexport )
//========================================================================================
#include "Entity2D.h"
//========================================================================================
using namespace std;
//========================================================================================
class Mesh : public Entity2D
{
public:
	Mesh(Renderer & renderer);
	~Mesh();

public:
	void setMeshData(const TexturedVertex* texVertex, Primitive ePrimitive, size_t uiVertexCount, const unsigned short* pusIndices, size_t uiIndexCount);
	void draw();
	void setTextureId(int iTextureId);
};
#endif