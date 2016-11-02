#include "Importer.h"
#include "Utility.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include <stack>
#include <iostream>
//=============================================================================================================
Importer::Importer(Renderer& renderer):
_renderer(renderer){}
//=============================================================================================================
Importer::~Importer(){}
//=============================================================================================================
bool Importer::importScene(const std::string& fileName, Nodo& rootNode){
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) return false;

	processNode(rootNode, *scene->mRootNode, *scene);

	return true;
}
//=============================================================================================================
bool Importer::processNode(Nodo& nodo, aiNode& assimpNode, const aiScene& scene){
	for (size_t j = 0; j < assimpNode.mNumMeshes; j++){
		Mesh* mesh = new Mesh(_renderer);

		aiMesh* _aiMesh = scene.mMeshes[assimpNode.mMeshes[j]];
		if (!_aiMesh) return false;

		TexturedVertex* verts = new TexturedVertex[_aiMesh->mNumVertices];
		if (_aiMesh->HasTextureCoords(0)){
			for (size_t i = 0; i < _aiMesh->mNumVertices; i++)
			{
				verts[i] = { _aiMesh->mVertices[i].x,
					_aiMesh->mVertices[i].y,
					_aiMesh->mVertices[i].z,
					_aiMesh->mTextureCoords[0][i].x,
					_aiMesh->mTextureCoords[0][i].y
				};
			}
		}

		else{
			for (size_t i = 0; i < _aiMesh->mNumVertices; i++){
				verts[i] = { _aiMesh->mVertices[i].x,
					_aiMesh->mVertices[i].y,
					_aiMesh->mVertices[i].z,
				};
			}
		}

		unsigned int numIndices = _aiMesh->mNumFaces * 3;
		unsigned short* indices = new unsigned short[numIndices];
		int index = 0;

		for (unsigned int i = 0; i < _aiMesh->mNumFaces; i++)
		{
			indices[i * 3 + 0] = _aiMesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = _aiMesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = _aiMesh->mFaces[i].mIndices[2];
		}

		mesh->setMeshData(verts, TRIANGLELIST, _aiMesh->mNumVertices, indices, numIndices);
		mesh->setName(_aiMesh->mName.C_Str());
		cout << _aiMesh->mName.C_Str() << endl;
		
		aiVector3t<float> position, scaling;
		aiQuaterniont<float> rotation;
		assimpNode.mTransformation.Decompose(scaling, rotation, position);

		mesh->setPosX(position.x);
		mesh->setPosY(position.y);
		mesh->setPosZ(position.z);
		mesh->setScale(scaling.x, scaling.y, scaling.z);
		mesh->setRotation(rotation.x, rotation.y, rotation.z);

		aiString path;
		std::stack<char> _stack;
		if (scene.mMaterials[_aiMesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			string fullPath = path.data;
			for (size_t i = fullPath.length(); i > 0; i--){
				if (fullPath[i] == '/')
					break;

				_stack.push(fullPath[i - 1]);
			}

			fullPath.clear();
			while (!_stack.empty()){
				fullPath += _stack.top();
				_stack.pop();
			}
			mesh->setTextureId(0, _renderer.loadTexture("Assets/" + fullPath, D3DCOLOR_XRGB(255, 0, 255)));
		}

		nodo.addChild(*mesh);
		mesh->setParent(&nodo);
	}

	for (size_t i = 0; i < assimpNode.mNumChildren; i++)
	{
		Nodo* nodoHijo = new Nodo();

		aiVector3t<float> position, scaling;
		aiQuaterniont<float> rotation;
		assimpNode.mTransformation.Decompose(scaling, rotation, position);
		nodoHijo->setName(assimpNode.mName.C_Str());
		cout << assimpNode.mName.C_Str() << endl;
		nodoHijo->setPosX(position.x);
		nodoHijo->setPosY(position.y);
		nodoHijo->setPosZ(position.z);
		nodoHijo->setScale(scaling.x , scaling.y, scaling.z );
		nodoHijo->setRotation(rotation.x, rotation.y, rotation.z);

		nodo.addChild(*nodoHijo);
		nodoHijo->setParent(&nodo);

		processNode(*nodoHijo, *assimpNode.mChildren[i], scene);
	}

	return true;
}
//=============================================================================================================