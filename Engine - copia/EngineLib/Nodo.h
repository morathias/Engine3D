#ifndef NODO_H
#define NODO_H
//=============================================================================
#include "Entity3D.h"
//=============================================================================
using namespace std;
//=============================================================================
class Nodo : public Entity3D
{
public:
	DllExport Nodo();
	DllExport ~Nodo();

	DllExport const vector<Entity3D*> childs() const;
	DllExport bool addChild(Entity3D& child);
	DllExport bool removeChild(Entity3D& child);

	DllExport void updateWorldTransformation();
	
	DllExport void draw(Renderer& renderer, CollisionResult parentResult,
		const Frustum& frustum, std::list <std::string>& names);
	DllExport void updateBV();
	DllExport void getNames(vector<std::string>& names, const Frustum& frustum);
private:
	vector<Entity3D*> _childs;
};
//=============================================================================
#endif
//=============================================================================