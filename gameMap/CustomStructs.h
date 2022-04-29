#ifndef CUSTOMSTRUCTS_H
#define CUSTOMSTRUCTS_H

#include "Island.h"

struct Level {
	int size; // amount of islands
	Island** islands; // island pointers array
	int** bridgesCoordinates; // a matrix with the coordiantes (size * size)
};

struct AntBuildParameters {
	int startCoordinate;
	int endCoordinate;
	int weight;
};

#endif
