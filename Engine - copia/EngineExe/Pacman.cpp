#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
Nodo* nodo1;
string userName;
bool Pacman::init(Renderer& rkRenderer){
	camera = new Camera();
	
	camera->setPos(0, 0, -100);

	_importer = new Importer(rkRenderer);
	if (!_importer->importScene("Assets/DemoTP8.dae", _root))
		cout << "no se cargo escena";
	nodo1 = new Nodo();
	nodo1 = (Nodo*)_root.childs()[0];
	
	return true;
}
//==================================================================================
float rotation = 0.0f;

void Pacman::frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer){
	if (input.keyDown(Input::KEY_D)){
		camera->strafe(15.0f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_A)){
		camera->strafe(-15.0f * (timer.timeBetweenFrames() / 1000.0f));
	}

	if (input.keyDown(Input::KEY_W)){
		camera->walk(15.0f * (timer.timeBetweenFrames() / 1000.0f));
	}
	else if (input.keyDown(Input::KEY_S)) {
		camera->walk(-15.0f * (timer.timeBetweenFrames() / 1000.0f));
	}

	camera->yaw(input.mouseRelPosX() * 0.005f);
	camera->pitch(input.mouseRelPosY() * 0.005f);
	camera->roll(input.mouseRelPosZ() * 0.0005f);

	camera->update(rkRenderer);
	if (input.keyDown(Input::KEY_RIGHT))
		nodo1->setPosX(nodo1->posX() + 0.01f);
	//moveRoot(input);
	//moveNode1(input);
	//moveMesh(input);
	//_root.updateWorldTransformation();
	_root.draw(rkRenderer, CollisionResult::AllInside, camera->getFrustum());
	_root.updateBV();
}
//==================================================================================
void Pacman::deinit(){
	delete camera;
}
//==================================================================================
void Pacman::moveNode1(Input& input){
	_root.childs()[1]->setRotation(0, _root.childs()[1]->rotationY() + 1.0f * -0.001f, 0);
}
//==================================================================================
void Pacman::moveMesh(Input& input){
	nodo1->childs()[0]->setRotation(nodo1->childs()[0]->rotationX() + 1.0f * 0.001f, 0, 0);
}
//==================================================================================
void Pacman::moveRoot(Input& input){
	_root.setRotation(0, 0, _root.rotationZ() + 1.0f * 0.001f);
}
//==================================================================================