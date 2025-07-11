#pragma once

#include <stdio.h>
#include <stdlib.h>

inline int GenerateRandomInt(int range_min, int range_max)
{
	int num = rand() % (range_max + 1 - range_min) + range_min;
	return num;
}

inline unsigned int GenerateRandomUInt(unsigned int range_min, unsigned int range_max)
{
	unsigned int num = rand() % (range_max + 1 - range_min) + range_min;
	return num;
}








