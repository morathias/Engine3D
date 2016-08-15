#ifndef VECTOR2_H
#define VECTOR2_H
//========================================================================================
#define DLLExport __declspec(dllexport)
//========================================================================================
class Vector2
{
public:
	DLLExport Vector2(float x, float y);
	DLLExport ~Vector2();

public:
	DLLExport float x();
	DLLExport float y();

public:
	DLLExport static Vector2 Normalize();
	DLLExport float getMagnitud();
private:
	float _x, _y;
};
//========================================================================================
#endif

