#ifndef PACMAN_H
#define PACMAN_H
//==================================================================================
#include <math.h>
#include <vector>
#include <list>
#include "Game.h"
#include "TileMap.h"
//==================================================================================
using namespace std;
//==================================================================================
class Pacman : public Game{
public:
	bool init(Renderer& rkRenderer);
	void frame(Renderer& rkRenderer, Input& input, pg1::Timer& timer);
	void deinit();

private:
	TileMap* tileMap;

	Sprite* _player;
	Animation* _runUp;
	Animation* _runDown;
	Animation* _runLeft;
	Animation* _runRight;
	Animation* _iddleDown;
	Animation* _iddleUp;
	Animation* _iddleRight;
	Animation* _iddleLeft;

	ScreenText _score;
	ScreenText _userName;

	Sound _sound;

	Quad quad;

	Camera* camera;
};
//==================================================================================
#endif
