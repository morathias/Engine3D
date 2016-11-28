#include "Nodo.h"
#include <algorithm>
#include <iostream>
using namespace std;
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
	float newMinPointX = FLT_MAX;
	float newMinPointY = FLT_MAX;
	float newMinPointZ = FLT_MAX;

	float newMaxPointX = FLT_MIN;
	float newMaxPointY = FLT_MIN;
	float newMaxPointZ = FLT_MIN;

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateBV();

		if (newMinPointX > _childs[i]->getAABB().min[0])
			newMinPointX = _childs[i]->getAABB().min[0];
		if (newMinPointY > _childs[i]->getAABB().min[1])
			newMinPointY = _childs[i]->getAABB().min[1];
		if (newMinPointZ > _childs[i]->getAABB().min[2])
			newMinPointZ = _childs[i]->getAABB().min[2];

		if (newMaxPointX < _childs[i]->getAABB().max[0])
			newMaxPointX = _childs[i]->getAABB().max[0];
		if (newMaxPointY < _childs[i]->getAABB().max[1])
			newMaxPointY = _childs[i]->getAABB().max[1];
		if (newMaxPointZ < _childs[i]->getAABB().max[2])
			newMaxPointZ = _childs[i]->getAABB().max[2];
	}
	_aabb.max[0] = newMaxPointX;
	_aabb.max[1] = newMaxPointY;
	_aabb.max[2] = newMaxPointZ;

	_aabb.min[0] = newMinPointX;
	_aabb.min[1] = newMinPointY;
	_aabb.min[2] = newMinPointZ;

	//std::cout << "min x: " << _aabb.min[0] << " min y: " << _aabb.min[1] << " min z: " << _aabb.min[2] << endl;
	//std::cout << "max x: " << _aabb.max[0] << " max y: " << _aabb.max[1] << " max z: " << _aabb.max[2] << endl;
}
//=====================================================================
