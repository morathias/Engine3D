#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
string userName;
bool Pacman::init(Renderer& rkRenderer){
	camera = new Camera();
	camera->setPos(0, 0, -100);

	unsigned short indices[] = { 0, 1, 2, 2, 1, 3, //front
								 4, 0, 6, 6, 0, 2, //right
								 7, 5, 6, 6, 5, 4, //back
								 3, 1, 7, 7, 1, 5, //left
								 4, 5, 0, 0, 5, 1, //upper
								 3, 7, 2, 2, 7, 6 }; //bottom
	Vertex _verts[8];

	_verts[0].x = -0.5f;	_verts[0].y = 0.5f;		_verts[0].z = -0.5f;	_verts[0].color = D3DCOLOR_ARGB(255, 50, 9, 35);
	_verts[1].x = 0.5f;		_verts[1].y = 0.5f;		_verts[1].z = -0.5f;	_verts[1].color = D3DCOLOR_ARGB(255, 100, 100, 100);
	_verts[2].x = -0.5f;	_verts[2].y = -0.5f;	_verts[2].z = -0.5f;	_verts[2].color = D3DCOLOR_ARGB(255, 100, 70, 100);
	_verts[3].x = 0.5f;		_verts[3].y = -0.5f;	_verts[3].z = -0.5f;	_verts[3].color = D3DCOLOR_ARGB(255, 200, 100, 100);
	_verts[4].x = -0.5f;	_verts[4].y = 0.5f;		_verts[4].z = 0.5f;		_verts[4].color = D3DCOLOR_ARGB(255, 222, 90, 200);
	_verts[5].x = 0.5f;		_verts[5].y = 0.5f;		_verts[5].z = 0.5f;		_verts[5].color = D3DCOLOR_ARGB(255, 200, 200, 99);
	_verts[6].x = -0.5f;	_verts[6].y = -0.5f;	_verts[6].z = 0.5f;		_verts[6].color = D3DCOLOR_ARGB(255, 200, 32, 200);
	_verts[7].x = 0.5f;		_verts[7].y = -0.5f;	_verts[7].z = 0.5f;		_verts[7].color = D3DCOLOR_ARGB(255, 255, 10, 111);

	cuboEstatico = new Mesh(rkRenderer);
	cuboEstatico->setMeshData(_verts, Primitive::TRIANGLELIST, ARRAYSIZE(_verts), indices, ARRAYSIZE(indices));
	cuboEstatico->setPosX(20);
	cuboEstatico->setPosY(20);
	cuboEstatico->setPosZ(20);
	cuboEstatico->setScale(50, 50, 50);
	_meshes.push_back(cuboEstatico);

	cuboRotando = new Mesh(rkRenderer);
	cuboRotando->setMeshData(_verts, Primitive::TRIANGLELIST, ARRAYSIZE(_verts), indices, ARRAYSIZE(indices));
	cuboRotando->setPosX(100);
	cuboRotando->setPosY(100);
	cuboRotando->setPosZ(100);
	cuboRotando->setScale(50, 50, 50);
	_meshes.push_back(cuboRotando);

	torus = new Mesh(rkRenderer);
	_importer.importMesh("Assets/taurus.obj", *torus);
	torus->setTextureId(0, rkRenderer.loadTexture("Assets/TexturesCom_Cliffs0180_1_seamless_S.jpg", D3DCOLOR_XRGB(255, 255, 255)));
	torus->setScale(35, 35, 35);
	torus->setPosZ(200);

	teaPot = new Mesh(rkRenderer);
	_importer.importMesh("Assets/teapot.obj", *teaPot);
	teaPot->setTextureId(0, rkRenderer.loadTexture("Assets/TexturesCom_Cliffs0180_1_seamless_S.jpg", D3DCOLOR_XRGB(255, 255, 255)));
	teaPot->setScale(1, 1, 1);
	teaPot->setPosX(-100);
	return true;
}
//==================================================================================
float rotation = 0.0f;

void Pacman::frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer){
	if (input.keyDown(Input::KEY_D)){
		camera->strafe(15.0f * (timer.timeBetweenFrames() / 100));
	}
	else if (input.keyDown(Input::KEY_A)){
		camera->strafe(-15.0f * (timer.timeBetweenFrames() / 100));
	}

	if (input.keyDown(Input::KEY_W)){
		camera->walk(15.0f * (timer.timeBetweenFrames() / 100));
	}
	else if (input.keyDown(Input::KEY_S)) {
		camera->walk(-15.0f * (timer.timeBetweenFrames() / 100));
	}

	camera->yaw(input.mouseRelPosX() * 0.005);
	camera->pitch(input.mouseRelPosY() * 0.005);
	camera->roll(input.mouseRelPosZ() * 0.0005);

	for (size_t i = 0; i < _meshes.size(); i++)
	{
		_meshes[i]->draw();
	}

	torus->draw();
	teaPot->draw();
	cuboRotando->setRotation(rotation, rotation, rotation);
	rotation += 0.003f;

	camera->update(rkRenderer);
}
//==================================================================================
void Pacman::deinit(){
	//delete cuboEstatico;
	//delete cuboRotando;
	//delete teaPot;
	//delete torus;
	delete camera;
	
}
//==================================================================================