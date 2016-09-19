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

	const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate |
													   aiProcess_JoinIdenticalVertices |
													   aiProcess_SortByPType|
													   aiProcess_ConvertToLeftHanded
													   );
	if (!scene){
		return false;
	}

	const aiMesh* _aiMesh = scene->mMeshes[0];
	if (!_aiMesh){
		return false;
	}
	
	TexturedVertex* verts = new TexturedVertex[_aiMesh->mNumVertices];
	for (size_t i = 0; i < _aiMesh->mNumVertices; i++)
	{
		if (_aiMesh->HasPositions()){
			verts[i].x = _aiMesh->mVertices[i].x;
			verts[i].y = _aiMesh->mVertices[i].y;
			verts[i].z = _aiMesh->mVertices[i].z;
		}
		if (_aiMesh->HasTextureCoords(0)){
			verts[i].u = _aiMesh->mTextureCoords[0][i].x;
			verts[i].v = _aiMesh->mTextureCoords[0][i].y;
		}
	}

	unsigned short numIndices = _aiMesh->mNumFaces * 3;
	unsigned short* indices = new unsigned short[numIndices];
	int index = 0;

	for (size_t i = 0; i < _aiMesh->mNumFaces; i++)
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
	}

	mesh.setMeshData(verts, TRIANGLELIST, _aiMesh->mNumVertices, indices, numIndices);
	
	return true;
}