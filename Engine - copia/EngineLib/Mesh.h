#ifndef MESH_H
#define MESH_H
//========================================================================================
#define DllExport __declspec( dllexport )
//========================================================================================
#include "Entity3D.h"
//========================================================================================
using namespace std;
//========================================================================================
class Mesh : public Entity3D
{
public:
	DllExport Mesh(Renderer& renderer);
	DllExport ~Mesh();

public:
	DllExport void setMeshData(const TexturedVertex* texVertex, 
							   Primitive ePrimitive, 
							   size_t uiVertexCount, 
							   const unsigned short* pusIndices, 
							   size_t uiIndexCount);

	DllExport void setMeshData(const Vertex* texVertex,
								Primitive ePrimitive,
								size_t uiVertexCount,
								const unsigned short* pusIndices,
								size_t uiIndexCount);
	DllExport void draw();
	DllExport void setTextureId(int iTextureId);

private:
	Renderer _renderer;
	Primitive _primitive;
};
//========================================================================================
#endif