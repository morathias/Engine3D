#include "Nodo.h"
//=====================================================================
Nodo::Nodo(){}
//=====================================================================
Nodo::~Nodo(){
	if (!_childs.empty()){
		for (size_t i = 0; i < _childs.size(); i++)
			delete _childs[i];
	}
}
//=====================================================================
bool Nodo::addChild(Entity3D& child){
	_childs.push_back(&child);
	return true;
}
//=====================================================================
bool Nodo::removeChild(Entity3D& child){
	vector<Entity3D*>::iterator _remove;
	_remove = std::find(_childs.begin(), _childs.end(), &child);

	if (_remove != _childs.end()){
		_childs.erase(_remove);
		return true;
	}
	
	else return false;
}
//=====================================================================
void Nodo::updateWorldTransformation(){
	Entity3D::updateWorldTransformation();

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateWorldTransformation();
	}
}
//=====================================================================
void Nodo::draw(Renderer& renderer, CollisionResult parentResult,
				const Frustum& frustum){
	if (!_parent) updateWorldTransformation();

	if (parentResult == AllOutside) return;

	/*if (parentResult == PartiallyInside){
		bool maxIn, minIn;

		maxIn = frustum.pointInFrustum(_aabb.maxPoint);
		minIn = frustum.pointInFrustum(_aabb.minPoint);

		if (maxIn && minIn){
			for (size_t i = 0; i < _childs.size(); i++){
				_childs[i]->draw(renderer, AllInside, frustum);
			}
		}
		else if (!maxIn && !minIn){
			for (size_t i = 0; i < _childs.size(); i++){
				_childs[i]->draw(renderer, AllOutside, frustum);
			}
		}
		else if (maxIn && !minIn || !maxIn && minIn){
			for (size_t i = 0; i < _childs.size(); i++){
				_childs[i]->draw(renderer, PartiallyInside, frustum);
			}
		}
	}*/

	if (parentResult == AllInside){
		for (size_t i = 0; i < _childs.size(); i++){
			_childs[i]->draw(renderer, AllInside, frustum);
		}
	}
}
//=====================================================================
const vector<Entity3D*> Nodo::childs() const{
	return _childs;
}
//=====================================================================
void Nodo::updateBV(){
	
}
//=====================================================================
