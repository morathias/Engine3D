#ifndef RANDOM_H
#define RANDOM_H
//===============================================================
#include <time.h>
#include <stdlib.h>
//===============================================================
#include "DllExport.h"
//===============================================================
class Random{
public:
	DllExport static int valueBetweenInts(int min, int max);
};
//===============================================================
#endif