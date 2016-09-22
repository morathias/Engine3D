#ifndef CAMERA_H
#define CAMERA_H
//==================================================================================
#include "DllExport.h"
//==================================================================================
#include "Renderer.h"
//==================================================================================
struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;
//==================================================================================
class Camera
{
public:
	DllExport Camera();
	DllExport ~Camera();

public:
	DllExport void roll(float value);
	DllExport void pitch(float value);
	DllExport void yaw(float value);

	DllExport void walk(float value);
	DllExport void strafe(float value);
	DllExport void fly(float value);

public:
	DllExport void setPos(float x, float y, float z);
	DllExport void setForward(float x, float y, float z);

	DllExport void update(Renderer& renderer);

private:
	Vector3 _eye;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _right;

	Matrix _viewMatrix;
};
//==================================================================================
#endif

