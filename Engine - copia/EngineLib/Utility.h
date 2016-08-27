#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
//========================================================================================
struct Vertex{
	float x, y, z;
	DWORD color;
};
//========================================================================================
struct TexturedVertex{
	float x, y, z;
	float u, v;
};
//========================================================================================
enum Primitive{
	POINTLIST = 0,
	LINELIST,
	LINESTRIP,
	TRIANGLELIST,
	TRIANGLESTRIP,
	TRIANGLEFAN,
	PRIMITIVE_COUNT
};
//========================================================================================
enum MatrixType{
	VIEW,
	PROJECTION,
	WORLD,
	MATRIX_TYPE_COUNT
};
//========================================================================================
#endif