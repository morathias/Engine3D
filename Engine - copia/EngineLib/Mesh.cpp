#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
//=====================================================
Mesh::Mesh(Renderer& renderer){
	_renderer = renderer;
}
//=====================================================
Mesh::~Mesh(){
}
//=====================================================
void Mesh::setMeshData(const TexturedVertex* texVertex, 
					   Primitive ePrimitive, 
					   size_t uiVertexCount, 
					   const unsigned short* pusIndices, 
					   size_t uiIndexCount)
{
	_primitive = ePrimitive;

	pg2::IndexBuffer* indexBuffer = _renderer.createIndexBuffer();
	pg2::VertexBuffer* vertexBuffer = _renderer.createVertexBuffer(sizeof(TexturedVertex), 0);

	vertexBuffer->setVertexData(texVertex, uiVertexCount);
	indexBuffer->setIndexData(pusIndices, uiIndexCount);

	_renderer.setCurrentIndexBuffer(indexBuffer);
	_renderer.setCurrentVertexBuffer(vertexBuffer);
}
//=====================================================
void Mesh::setMeshData(const Vertex* texVertex,
	Primitive ePrimitive,
	size_t uiVertexCount,
	const unsigned short* pusIndices,
	size_t uiIndexCount)
{
	_primitive = ePrimitive;

	pg2::IndexBuffer* indexBuffer = _renderer.createIndexBuffer();
	pg2::VertexBuffer* vertexBuffer = _renderer.createVertexBuffer(sizeof(Vertex), 1);

	vertexBuffer->setVertexData(texVertex, uiVertexCount);
	indexBuffer->setIndexData(pusIndices, uiIndexCount);

	_renderer.setCurrentIndexBuffer(indexBuffer);
	_renderer.setCurrentVertexBuffer(vertexBuffer);
}
//=====================================================
void Mesh::draw(){
	_renderer.setMatrix(MatrixType::WORLD, _transformationMatrix);
	_renderer.drawCurrentBuffers(_primitive);
}
//=====================================================
void Mesh::setTextureId(int iTextureId){

}
//=====================================================
