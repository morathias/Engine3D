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
//========================================================================================
class Entity3D
{
public:
	DllExport Entity3D();
	DllExport ~Entity3D();
	DllExport void setPosX(float fPosX);
	DllExport void setPosY(float fPosY);
	DllExport void setPosZ(float fPosZ);
	DllExport void setRotation(float fRotation);
	DllExport void setScale(float fScaleX, float fScaleY);
	DllExport void setScale(float fScaleX, float fScaleY, float scaleZ);

	DllExport void flipNot();
	DllExport void Flip();

	DllExport CollisionResult3D checkCollision(Entity3D& toCheck);

	DllExport void returnToPreviusPos(float fPosX, float fPosY);
	DllExport void returnToPreviusPosH();
	DllExport void returnToPreviusPosV();

	DllExport float posX() const;
	DllExport float posY() const;
	DllExport float posZ() const;

	DllExport float previusPosX() const;
	DllExport float previusPosY() const;

	DllExport float rotation() const;
	DllExport float scaleX() const;
	DllExport float scaleY() const;
	DllExport float scaleZ() const;

protected:
	void updateLocalTransformation();
	float _posX;
	float _posY;
	float _posZ;
	float _previusPosX;
	float _previusPosY;
	float _rotation;
	float _scaleX;
	float _scaleY;
	float _scaleZ;
	bool _flip;

	Matrix _transformationMatrix;

};
//========================================================================================
#endif

