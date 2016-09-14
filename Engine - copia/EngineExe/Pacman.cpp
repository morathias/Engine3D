#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
string userName;
bool Pacman::init(Renderer& rkRenderer){
	/*
	_sound.open("Assets/wind.mp3", true);
	_sound.play();
	userName = "MatyX";
	string passWord = "None";

	tileMap = new TileMap();
	tileMap->importTileMap("assets/tilemap4.tmx", rkRenderer);
	
	_score.create(0, 0, 1000, 100, 50, "Arial", "Hola", false, rkRenderer);
	_userName.create(0, 50, 1000, 200, 50, "Arial", "UserName: ", false, rkRenderer);

	_player = new Sprite();
	_player->setPosX(0);
	_player->setPosY(-100);
	_player->setTexture(rkRenderer.loadTexture("assets/samurai.png", D3DCOLOR_XRGB(255, 255, 255)));
	_player->setScale(100, 100);
	quad.setScale(32, 32);

	_iddleDown = new Animation();
	_iddleDown->addFrame(0.0f, 0.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.6f, 4);
	_iddleLeft = new Animation();
	_iddleLeft->addFrame(0.0f, 64.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.6f, 4);

	_runDown = new Animation();
	_runDown->addFrame(256.0f, 0.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.7f, 7);
	_runLeft = new Animation();
	_runLeft->addFrame(256.0f, 64.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.66f, 8);
	_runRight = new Animation();
	_runRight->addFrame(256.0f, 128.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.66f, 8);
	_runRight = new Animation();
	_runRight->addFrame(256.0f, 128.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.66f, 8);
	_runUp = new Animation();
	_runUp->addFrame(256.0f, 192.0f, 64.0f, 64.0f, 1024.0f, 1024.0f, 0.7f, 6);
	_player->setAnimation(_iddleDown);
	*/

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

	/*
	for (size_t i = 0; i < 100; i++)
	{
		Mesh* mesh = new Mesh(rkRenderer);
		mesh->setMeshData(_verts, Primitive::TRIANGLELIST, ARRAYSIZE(_verts), indices, ARRAYSIZE(indices));
		mesh->setPosX(Random::valueBetweenInts(-700, 700));
		mesh->setPosY(Random::valueBetweenInts(-700, 700));
		mesh->setPosZ(Random::valueBetweenInts(-700, 700));
		mesh->setScale(Random::valueBetweenInts(50, 300), Random::valueBetweenInts(50, 500), Random::valueBetweenInts(50, 300));
		_meshes.push_back(mesh);
	}
	*/
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

	return true;
}
//==================================================================================
//int i = 0;
float rotation = 0.0f;
//string score;

void Pacman::frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer){
	//tileMap->draw(rkRenderer);
	
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

	/*
	if (input.keyUp(Input::KEY_S) && input.keyUp(Input::KEY_A) && input.keyUp(Input::KEY_D) && input.keyUp(Input::KEY_W)){
		_player->setAnimation(_iddleDown);
	}

	tileMap->checkCollision(*_player);

	_player->update(timer);
	_player->draw(rkRenderer);
	*/

	for (size_t i = 0; i < _meshes.size(); i++)
	{
		_meshes[i]->draw();
	}

	cuboRotando->setRotation(rotation);
	rotation += 0.003f;

	camera->update(rkRenderer);

	/*
	i++;
	score = "Score: " + std::to_string(i);
	_score.setText(score);
	_score.display(rkRenderer);
	_userName.setText("Username: " + userName);
	_userName.display(rkRenderer);
	*/

	
}
//==================================================================================
void Pacman::deinit(){
}
//==================================================================================