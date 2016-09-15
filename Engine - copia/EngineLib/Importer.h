#ifndef IMPORTER_H
#define IMPORTER_H
//=============================================================
#include "Mesh.h"
#include <string>
//=============================================================
class Importer
{
public:
	Importer();
	~Importer();

	bool importMesh(const std::string& fileName, Mesh& mesh);
};
//=============================================================
#endif

