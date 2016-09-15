#include "Entity3D.h"
//==================================================================================
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include <algorithm>
//==================================================================================
using namespace std;
//==================================================================================
Entity3D::Entity3D()
	:
	_transformationMatrix(new D3DXMATRIX()),
	_posX(0),
	_posY(0),
	_posZ(0),
	_previusPosX(0),
	_previusPosY(0),
	_rotationX(0),
	_rotationY(0),
	_rotationZ(0),
	_scaleX(100.0f),
	_scaleY(100.0f),
	_scaleZ(100.0f)
{}
//==================================================================================
Entity3D::~Entity3D(){
}
//==================================================================================
void Entity3D::setPosX(float fPosX){
	_previusPosX = _posX;

	_posX = fPosX;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::setPosY(float fPosY){
	_previusPosY = _posY;

	_posY = fPosY;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::setPosZ(float fPosZ){
	_posZ = fPosZ;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::setRotation(float rotationX, float rotationY, float rotationZ){
	_rotationX = rotationX;
	_rotationY = rotationY;
	_rotationZ = rotationZ;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::setScale(float fScaleX, float fScaleY){
	_scaleX = fScaleX;
	_scaleY = fScaleY;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::setScale(float fScaleX, float fScaleY, float scaleZ){
	_scaleX = fScaleX;
	_scaleY = fScaleY;
	_scaleZ = scaleZ;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::Flip(bool flipped){
	if (flipped && _scaleX > 0)
		_scaleX = -(_scaleX);
}
//==================================================================================
CollisionResult3D Entity3D::checkCollision(Entity3D& toCheck){
	float overlapX = max(0.0f,
		min(posX() + fabs(scaleX()) / 2.0f, toCheck.posX() + fabs(toCheck.scaleX()) / 2.0f) -
		max(posX() - fabs(scaleX()) / 2.0f, toCheck.posX() - fabs(toCheck.scaleX()) / 2.0f));

	float overlapY = max(0.0f,
		min(posY() + fabs(scaleY()) / 2.0f, toCheck.posY() + fabs(toCheck.scaleY()) / 2.0f) -
		max(posY() - fabs(scaleY()) / 2.0f, toCheck.posY() - fabs(toCheck.scaleY()) / 2.0f));

	if (overlapX != 0.0f && overlapY != 0.0f)
	{
		if (overlapX > overlapY)
		{
			if (posY() < 0 && posY() < toCheck.posY() || posY() > 0 && posY() < toCheck.posY()){
				return Collision_Y_Up;
			}
			else if (posY() < 0 && posY() > toCheck.posY() || posY() > 0 && posY() > toCheck.posY()){
				return Collision_Y_Down;
			}
		}
		else
		{
			if (posX() < 0 && posX() < toCheck.posX() || posX() > 0 && posX() < toCheck.posX())
				return Collision_X_Right;
			else if (posX() < 0 && posX() > toCheck.posX() || posX() > 0 && posX() > toCheck.posX())
				return Collision_X_Left;
		}
	}
	return NoCollision_3D;
}
//==================================================================================
void Entity3D::returnToPreviusPos(float fPosX, float fPosY){
	_posX = fPosX;
	_posY = fPosY;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::returnToPreviusPosH(){
	_posX = _previusPosX;

	updateLocalTransformation();
}
//==================================================================================
void Entity3D::returnToPreviusPosV(){
	_posY = _previusPosY;

	updateLocalTransformation();
}
//==================================================================================
float Entity3D::posX() const{
	return _posX;
}
//==================================================================================
float Entity3D::posY() const{
	return _posY;
}
//==================================================================================
float Entity3D::posZ() const{
	return _posZ;
}
//==================================================================================
float Entity3D::previusPosX() const{
	return _previusPosX;
}
//==================================================================================
float Entity3D::previusPosY() const{
	return _previusPosY;
}
//==================================================================================
float Entity3D::rotationX() const{
	return _rotationX;
}
//==================================================================================
float Entity3D::rotationY() const{
	return _rotationY;
}
//==================================================================================
float Entity3D::rotationZ() const{
	return _rotationZ;
}
//==================================================================================
float Entity3D::scaleX() const{
	return _scaleX;
}
//==================================================================================
float Entity3D::scaleY() const{
	return _scaleY;
}
//==================================================================================
void Entity3D::updateLocalTransformation(){

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, _posZ);

	D3DXMATRIX rotationMat;
	D3DXMATRIX rotX, rotY, rotZ;

	D3DXMatrixRotationX(&rotX, _rotationX);
	D3DXMatrixRotationY(&rotY, _rotationY);
	D3DXMatrixRotationZ(&rotZ, _rotationZ);

	rotationMat = rotX * rotY * rotZ;

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &traslatrionMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &scaleMat, _transformationMatrix);
}
//==================================================================================