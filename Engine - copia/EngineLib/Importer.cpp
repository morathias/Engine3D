#include "Importer.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
//================================================
Importer::Importer(){
}
//================================================
Importer::~Importer(){
}
//================================================
bool Importer::importMesh(const std::string& fileName, Mesh& mesh){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName, aiProcess_CalcTangentSpace |
													   aiProcess_Triangulate);
	return true;
}