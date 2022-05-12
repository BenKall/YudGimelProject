
#include "CustomStructs.h"

bool operator<(GraphPoint const& _Left, GraphPoint const& _Right) {
	return (_Left.weight < _Right.weight);
}