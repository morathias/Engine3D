#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
//=====================================================
Mesh::Mesh(Renderer& renderer):
	_renderer (renderer),
	_texture (NoTexture)
{}
//=====================================================
Mesh::~Mesh(){
	delete _vertexBuffer;
	_vertexBuffer = NULL;
	delete _indexBuffer;
	_indexBuffer = NULL;
}
//=====================================================
void Mesh::setMeshData(const TexturedVertex* texVertex, 
					   Primitive ePrimitive, 
					   size_t uiVertexCount, 
					   const unsigned short* pusIndices, 
					   size_t uiIndexCount)
{
	_primitive = ePrimitive;

	_indexBuffer = _renderer.createIndexBuffer();
	_vertexBuffer = _renderer.createVertexBuffer(sizeof(TexturedVertex), 0);

	_vertexBuffer->setVertexData(texVertex, uiVertexCount);
	_indexBuffer->setIndexData(pusIndices, uiIndexCount);

	_renderer.setCurrentIndexBuffer(_indexBuffer);
	_renderer.setCurrentVertexBuffer(_vertexBuffer);
}
//=====================================================
void Mesh::setMeshData(const Vertex* texVertex,
					   Primitive ePrimitive,
					   size_t uiVertexCount,
					   const unsigned short* pusIndices,
					   size_t uiIndexCount)
{
	_primitive = ePrimitive;

	_indexBuffer = _renderer.createIndexBuffer();
	_vertexBuffer = _renderer.createVertexBuffer(sizeof(Vertex), 1);

	_vertexBuffer->setVertexData(texVertex, uiVertexCount);
	_indexBuffer->setIndexData(pusIndices, uiIndexCount);

	_renderer.setCurrentIndexBuffer(_indexBuffer);
	_renderer.setCurrentVertexBuffer(_vertexBuffer);
}
//=====================================================
void Mesh::draw(){
	_renderer.setCurrentTexture(_texture);
	_renderer.setMatrix(MatrixType::WORLD, _worldTransformationMatrix);

	_vertexBuffer->bind();
	_indexBuffer->bind();

	_renderer.drawCurrentBuffers(_primitive);
}
//=====================================================
void Mesh::setTextureId(int iTextureId, Texture texture){
	_texture = texture;
}
//=====================================================
