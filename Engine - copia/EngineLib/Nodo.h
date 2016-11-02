#ifndef NODO_H
#define NODO_H

#include "Entity3D.h"

using namespace std;

class Nodo : public Entity3D
{
public:
	DllExport Nodo();
	DllExport ~Nodo();

	DllExport const vector<Entity3D*> childs() const;
	DllExport bool addChild(Entity3D& child);
	DllExport bool removeChild(Entity3D& child);

	DllExport void showNames();

	DllExport void updateWorldTransformation();
	
	DllExport void draw();
private:
	vector<Entity3D*> _childs;
	vector<string> _names;
};

#endif

