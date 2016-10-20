#include "Importer.h"
#include "Utility.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
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
		for (size_t i = 0; i < _aiMesh->mNumVertices; i++)
		{
			verts[i] = { _aiMesh->mVertices[i].x,
				_aiMesh->mVertices[i].y,
				_aiMesh->mVertices[i].z,
				_aiMesh->mTextureCoords[0][i].x,
				_aiMesh->mTextureCoords[0][i].y
			};
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
		nodo.addChild(*mesh);
		mesh->setParent(&nodo);
	}

	for (size_t i = 0; i < assimpNode.mNumChildren; i++)
	{
		Nodo* nodoHijo = new Nodo();

		nodo.addChild(*nodoHijo);
		nodoHijo->setParent(&nodo);
		processNode(*nodoHijo, assimpNode, scene);
	}

	return true;
}
//=============================================================================================================