#include "Nodo.h"
<<<<<<< HEAD
//=====================================================================
Nodo::Nodo(){}
//=====================================================================
Nodo::~Nodo(){}
//=====================================================================
=======


Nodo::Nodo(){}


Nodo::~Nodo()
{
}

>>>>>>> origin/master
bool Nodo::addChild(Entity3D& child){
	_childs.push_back(&child);
	return true;
}
<<<<<<< HEAD
//=====================================================================
=======

>>>>>>> origin/master
bool Nodo::removeChild(Entity3D& child){
	vector<Entity3D*>::iterator _remove;
	_remove = std::find(_childs.begin(), _childs.end(), &child);

	if (_remove != _childs.end()){
		_childs.erase(_remove);
		return true;
	}
	
<<<<<<< HEAD
	else return false;
}
//=====================================================================
=======
	else
	{
		return false;
	}
}

>>>>>>> origin/master
void Nodo::updateWorldTransformation(){
	Entity3D::updateWorldTransformation();

	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->updateWorldTransformation();
	}
}
<<<<<<< HEAD
//=====================================================================
void Nodo::draw(){
	for (size_t i = 0; i < _childs.size(); i++){
		_childs[i]->draw();
	}
}
//=====================================================================
const vector<Entity3D*> Nodo::childs() const{
	return _childs;
}
//=====================================================================
=======
>>>>>>> origin/master
