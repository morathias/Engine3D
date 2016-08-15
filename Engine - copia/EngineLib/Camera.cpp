#include "Camera.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib") 
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib") 

Camera::Camera(Renderer& renderer){
	_renderer = renderer;

	_eye = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_right = new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up = new D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	_lookAt = new D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

Camera::~Camera(){
	delete _eye;
	delete _right;
	delete _up;
	delete _lookAt;
}

void Camera::roll(float value){
}

void Camera::pitch(float value){
}

void Camera::yaw(float value){
}

void Camera::walk(float value){
}

void Camera::strafe(float value){
}

void Camera::fly(float value){
}

void Camera::setPos(float x, float y, float z){
	_eye->x = x;
	_eye->y = y;
	_eye->z = z;
}

void Camera::setForward(float x, float y, float z){
	_lookAt->x = x;
	_lookAt->y = y;
	_lookAt->z = z;
}

void Camera::update(){

}