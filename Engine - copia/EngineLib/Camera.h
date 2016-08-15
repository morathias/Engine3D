#ifndef CAMERA_H
#define CAMERA_H

#define DLLexport __declspec(dllexport)

#include "Renderer.h"

struct D3DXVECTOR3;
typedef D3DXVECTOR3* Vector3;

class Camera
{
public:
	DLLexport Camera(Renderer& renderer);
	DLLexport ~Camera();

public:
	DLLexport void roll(float value);
	DLLexport void pitch(float value);
	DLLexport void yaw(float value);

	DLLexport void walk(float value);
	DLLexport void strafe(float value);
	DLLexport void fly(float value);

public:
	DLLexport void setPos(float x , float y, float z);
	DLLexport void setForward(float x, float y, float z);

	DLLexport void update();

private:
	Vector3 _eye;
	Vector3 _lookAt;
	Vector3 _up;
	Vector3 _right;

	Renderer _renderer;

	Matrix _viewMatrix;
};
#endif

