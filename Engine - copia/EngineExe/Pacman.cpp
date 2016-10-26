#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
string userName;
bool Pacman::init(Renderer& rkRenderer){
	camera = new Camera();
	camera->setPos(0, 0, -100);

	_importer = new Importer(rkRenderer);
	if (!_importer->importScene("Assets/nanosuit.dae", _root))
		cout << "no se cargo escena";

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

	camera->yaw(input.mouseRelPosX() * 0.005f);
	camera->pitch(input.mouseRelPosY() * 0.005f);
	camera->roll(input.mouseRelPosZ() * 0.0005f);

	camera->update(rkRenderer);

	moveRoot(input);
	
	_root.draw();
}
//==================================================================================
void Pacman::deinit(){
	delete camera;
}
//==================================================================================
void Pacman::moveNode1(Input& input){
	/*if (input.keyDown(input.KEY_K)){
		_node1.setRotation(0, _node1.rotationY() + 1.0f * 0.001f, 0);
	}

	else if (input.keyDown(input.KEY_L)){
		_node1.setRotation(0, _node1.rotationY() + 1.0f * -0.001f, 0);
	}*/
}
//==================================================================================
void Pacman::moveMesh(Input& input){
	/*if (input.keyDown(input.KEY_N)){
		torus->setRotation(0, 0, torus->rotationZ() + 1.0f * 0.001f);
	}

	else if (input.keyDown(input.KEY_M)){
		torus->setRotation(0, 0, torus->rotationZ() + 1.0f * -0.001f);
	}*/
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