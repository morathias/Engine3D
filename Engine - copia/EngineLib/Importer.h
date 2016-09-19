#ifndef IMPORTER_H
#define IMPORTER_H
//=============================================================
#include "Mesh.h"
#include <string>
//=============================================================
class Importer
{
public:
	DllExport Importer();
	DllExport ~Importer();

	DllExport bool importMesh(const std::string& fileName, Mesh& mesh);
};
//=============================================================
#endif

