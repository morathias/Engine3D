#include "Nodo.h"


Nodo::Nodo(){}


Nodo::~Nodo()
{
}

bool Nodo::addChild(Entity3D& child){
	_childs.push_back(&child);
	return true;
}

bool Nodo::removeChild(Entity3D& child){
	vector<Entity3D*>::iterator _remove;
	_remove = std::find(_childs.begin(), _childs.end(), &child);

	if (_remove != _childs.end()){
		_childs.erase(_remove);
		return true;
	}
	
	else
	{
		return false;
	}
}

void Nodo::updateWorldTransformation(){
	Entity3D::updateWorldTransformation();

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateWorldTransformation();
	}
}
