#include "Pacman.h"
#include "input.h"
#include <iostream>
//==================================================================================
string userName;
bool Pacman::init(Renderer& rkRenderer){
	
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
	_player->setPosZ(0);
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

	camera = new Camera();
	camera->setPos(0, -100, -100);
	return true;
}
//==================================================================================
int i = 0;
string score;

void Pacman::frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer){
	tileMap->draw(rkRenderer);
	
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

	if (input.keyUp(Input::KEY_S) && input.keyUp(Input::KEY_A) && input.keyUp(Input::KEY_D) && input.keyUp(Input::KEY_W)){
		_player->setAnimation(_iddleDown);
	}

	tileMap->checkCollision(*_player);

	_player->update(timer);
	_player->draw(rkRenderer);

	camera->update(rkRenderer);

	i++;
	score = "Score: " + std::to_string(i);
	_score.setText(score);
	_score.display(rkRenderer);
	_userName.setText("Username: " + userName);
	_userName.display(rkRenderer);
}
//==================================================================================
void Pacman::deinit(){
}
//==================================================================================