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

	void moveRoot(Input& input);
	void moveNode1(Input& input);
	void moveMesh(Input& input);

private:
	Camera* camera;
	Mesh* cuboEstatico;
	Mesh* torus;
	Mesh* teaPot;
	Nodo _root;
	Nodo _node1;

	Importer* _importer;
};
//==================================================================================
#endif
