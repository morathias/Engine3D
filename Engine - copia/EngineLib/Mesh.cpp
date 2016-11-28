#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
#include "BoundingBox.h"
#include <algorithm>
#include <iostream>
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
	_verts = texVertex;

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
void Mesh::draw(Renderer& renderer, CollisionResult parentResult,
				const Frustum& frustum){
	//if (parentResult != CollisionResult::AllOutside){
	int pointsInFrustrum = 0;

	for (size_t i = 0; i < 8; i++){
		if (frustum.pointInFrustum(points[i]))
			pointsInFrustrum++;
	}

	if (pointsInFrustrum > 0){
		//std::cout << "se dibuja"<< endl;
		_renderer.setCurrentTexture(_texture);
		_renderer.setMatrix(MatrixType::WORLD, _worldTransformationMatrix);

		_vertexBuffer->bind();
		_indexBuffer->bind();

		_renderer.drawCurrentBuffers(_primitive);
	}
	//updateBV();
	//_boundingBox->draw(renderer, parentResult, frustum);
	//_boundingBox->setScale(100, 100, 100);
}
//=====================================================
void Mesh::setTextureId(int iTextureId, Texture texture){
	_texture = texture;
}
//=====================================================
void Mesh::updateBV(){
	D3DXVECTOR3 pos, scale;
	D3DXQUATERNION rot;
	D3DXMatrixDecompose(&scale, &rot, &pos, _worldTransformationMatrix);

	float auxMaxX, auxMaxY, auxMaxZ = 0;
	float auxMinX, auxMinY, auxMinZ = 0;

	auxMaxX = (_aabb.maxPointX + pos.x) * scale.x;
	auxMaxY = (_aabb.maxPointY + pos.y) * scale.y;
	auxMaxZ = (_aabb.maxPointZ + pos.z) * scale.z;

	auxMinX = (_aabb.minPointX + pos.x) * scale.x;
	auxMinY = (_aabb.minPointY + pos.y) * scale.y;
	auxMinZ = (_aabb.minPointZ + pos.z) * scale.z;

	//std::cout << "x: " << scale.x << " y: " << scale.y << " z: " << scale.z << endl;
	//std::cout << "x: " << pos.x << " y: " << pos.y << " z: " << pos.z << endl;
	//std::cout << "x: " << auxMaxX << " y: " << auxMaxY << " z: " << auxMaxZ << endl;
	//std::cout << "x: " << auxMinX << " y: " << auxMinY << " z: " << auxMinZ << endl;

	points[0]->x = auxMinX;		points[0]->y = auxMaxY;		points[0]->z = auxMinZ;
	points[1]->x = auxMaxX;		points[1]->y = auxMaxY;		points[1]->z = auxMinZ;
	points[2]->x = auxMinX;		points[2]->y = auxMinY;		points[2]->z = auxMinZ;
	points[3]->x = auxMaxX;		points[3]->y = auxMinY;		points[3]->z = auxMinZ;
	points[4]->x = auxMinX;		points[4]->y = auxMaxY;		points[4]->z = auxMaxZ;
	points[5]->x = auxMaxX;		points[5]->y = auxMaxY;		points[5]->z = auxMaxZ;
	points[6]->x = auxMinX;		points[6]->y = auxMinY;		points[6]->z = auxMaxZ;
	points[7]->x = auxMaxX;		points[7]->y = auxMinY;		points[7]->z = auxMaxZ;

	_aabb.max[0] = auxMaxX;		_aabb.max[1] = auxMaxY;		_aabb.max[2] = auxMaxZ;
	_aabb.min[0] = auxMinX;		_aabb.min[1] = auxMinY;		_aabb.min[2] = auxMinZ;

	/*for (size_t i = 0; i < 8; i++)
	{
		std::cout << "x: " << _aabb.points[i]->x << " y: " << _aabb.points[i]->y << " z: " << _aabb.points[i]->z << endl;
	}*/
}
//=====================================================
void Mesh::buildAABB(){
	_aabb.minPointX = _verts[0].x; _aabb.minPointY = _verts[0].y; _aabb.minPointZ = _verts[0].z;
	_aabb.maxPointX = _verts[0].x; _aabb.maxPointY = _verts[0].y; _aabb.maxPointZ = _verts[0].z;

	for (size_t i = 1; i < _vertexBuffer->vertexCount(); i++){
		if (_verts[i].x < _aabb.minPointX)
			_aabb.minPointX = _verts[i].x;
		if (_verts[i].y < _aabb.minPointY)
			_aabb.minPointY = _verts[i].y;
		if (_verts[i].z < _aabb.minPointZ)
			_aabb.minPointZ = _verts[i].z;

		if (_verts[i].x > _aabb.maxPointX)
			_aabb.maxPointX = _verts[i].x;
		if (_verts[i].y > _aabb.maxPointY)
			_aabb.maxPointY = _verts[i].y;
		if (_verts[i].z > _aabb.maxPointZ)
			_aabb.maxPointZ = _verts[i].z;
	}

	std::cout << "min x: " << _aabb.minPointX << " min y: " << _aabb.minPointY << " min z: " << _aabb.minPointY << endl;
	std::cout << "max x: " << _aabb.maxPointX << " max y: " << _aabb.maxPointY << " max z: " << _aabb.maxPointY << endl;
}
//=====================================================
