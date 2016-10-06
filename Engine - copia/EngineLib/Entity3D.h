#ifndef ENTITY3D_H
#define ENTITY3D_H
//========================================================================================
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0]))) //dinamic array size
//========================================================================================
#include "Renderer.h"
//========================================================================================
enum CollisionResult3D
{
	Collision_Y_Up,
	Collision_Y_Down,
	Collision_X_Right,
	Collision_X_Left,
	NoCollision_3D
};
class Nodo;
//========================================================================================
class Entity3D
{
public:
	DllExport Entity3D();
	DllExport ~Entity3D();
	DllExport void setPosX(float fPosX);
	DllExport void setPosY(float fPosY);
	DllExport void setPosZ(float fPosZ);
	DllExport void setRotation(float rotationX, float rotationY, float rotationZ);
	DllExport void setScale(float fScaleX, float fScaleY);
	DllExport void setScale(float fScaleX, float fScaleY, float scaleZ);

	DllExport void Flip(bool flipped);

	DllExport CollisionResult3D checkCollision(Entity3D& toCheck);

	DllExport void returnToPreviusPos(float fPosX, float fPosY);
	DllExport void returnToPreviusPosH();
	DllExport void returnToPreviusPosV();

	DllExport float posX() const;
	DllExport float posY() const;
	DllExport float posZ() const;

	DllExport float previusPosX() const;
	DllExport float previusPosY() const;

	DllExport float rotationX() const;
	DllExport float rotationY() const;
	DllExport float rotationZ() const;

	DllExport float scaleX() const;
	DllExport float scaleY() const;
	DllExport float scaleZ() const;

	DllExport void setParent(Nodo* parent);
	DllExport const Matrix& worldMatrix() const;
	DllExport virtual void updateWorldTransformation();
	DllExport virtual void draw() = 0;

protected:
	void updateLocalTransformation();
	float _posX, _posY, _posZ;
	float _previusPosX, _previusPosY;

	float _rotationX, _rotationY, _rotationZ;

	float _scaleX, _scaleY, _scaleZ;

	Matrix _transformationMatrix;
	Matrix _worldTransformationMatrix;

	Nodo* _parent;
};
//========================================================================================
#endif

