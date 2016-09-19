#include "Importer.h"
#include "Utility.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include <iostream>
//================================================
Importer::Importer(){
}
//================================================
Importer::~Importer(){
}
//================================================
bool Importer::importMesh(const std::string& fileName, Mesh& mesh){
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate );
	if (!scene){
		return false;
	}

	const aiMesh* _aiMesh = scene->mMeshes[0];
	if (!_aiMesh){
		return false;
	}
	
	TexturedVertex* verts = new TexturedVertex[_aiMesh->mNumVertices];
	for (int i = 0; i < _aiMesh->mNumVertices; i++)
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

	/*for (size_t i = 0; i < _aiMesh->mNumFaces; i++)
	{
		const aiFace& face = _aiMesh->mFaces[i];
		if (face.mNumIndices == 3){
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices[index] = face.mIndices[j];
				cout << indices[index]<< " ";
				index++;
			}
		}
		cout << endl;
	}*/

	for (unsigned int i = 0; i < _aiMesh->mNumFaces; i++)
	{
		indices[i * 3 + 0] = _aiMesh->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = _aiMesh->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = _aiMesh->mFaces[i].mIndices[2];
	}

	mesh.setMeshData(verts, TRIANGLELIST, _aiMesh->mNumVertices, indices, numIndices);
	
	return true;
}