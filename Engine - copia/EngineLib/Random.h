#ifndef RANDOM_H
#define RANDOM_H
//===============================================================
#include <time.h>
#include <stdlib.h>
//===============================================================
#define DLLExport __declspec(dllexport)
//===============================================================
class Random{
public:
	DLLExport static int valueBetweenInts(int min, int max);
};
//===============================================================
#endif