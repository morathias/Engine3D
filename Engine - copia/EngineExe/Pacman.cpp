#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
string userName;
bool Pacman::init(Renderer& rkRenderer){
	camera = new Camera();
	camera->setPos(0, 0, -100);

	_importer = new Importer(rkRenderer);
	if (!_importer->importScene("Assets/demo.dae", _root))
		cout << "no se cargo escena";

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

	moveRoot(input);
	moveNode1(input);
	moveMesh(input);
	_root.draw();
}
//==================================================================================
void Pacman::deinit(){
	delete camera;
}
//==================================================================================
void Pacman::moveNode1(Input& input){
	if (input.keyDown(input.KEY_K))
		_root.childs()[0]->setRotation(_root.childs()[0]->rotationX() + 1.0f * -0.001f, 0, 0);
}
//==================================================================================
void Pacman::moveMesh(Input& input){
	if (input.keyDown(input.KEY_N))
		_root.childs()[2]->setRotation(_root.childs()[2]->rotationX() + 1.0f * -0.001f, 0, 0);
}
//==================================================================================
void Pacman::moveRoot(Input& input){
	if (input.keyDown(input.KEY_O)){
		_root.setRotation(_root.rotationX() + 1.0f * 0.001f, 0, 0);
	}

	else if (input.keyDown(input.KEY_P)){
		_root.setRotation(_root.rotationX() + 1.0f * -0.001f, 0, 0);
	}
}
//==================================================================================