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


struct GraphPoint {
	int num;
	int weight;
};

//__declspec(noinline) auto MyFunc(GraphPoint& _Left, GraphPoint& _Right)
//{
//	return (_Left.weight < _Right.weight);
//}

bool operator<(GraphPoint const& _Left, GraphPoint const& _Right);

//bool operator<(GraphPoint const& _Left, GraphPoint const& _Right) {
//	return (_Left.weight < _Right.weight);
//}


//constexpr bool operator()(const _Ty& _Left, const _Ty& _Right) const
//{	// apply operator< to operands
//	return (_Left < _Right);
//}
//	};

#endif
