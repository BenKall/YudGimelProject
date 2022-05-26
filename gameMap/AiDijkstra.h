#ifndef AIDIJKSTRA_H
#define AIDIJKSTRA_H
#include "AiEnemy.h"

class AiDijkstra :
	public AiEnemy
{
public:
	AiDijkstra(Level mapLayout);
	std::vector<AntBuildParameters> Think(Level curMapStatus);
	int minDistance(int* dist, bool* sptSet);
	int printSolution(int* dist, int* parent);
	void printPath(int* parent, int j);
	void dijkstra(int src);
	void setPath(int* parent, int j);


private:
	//std::list<GraphPoint>* adj;
	/*int* processed;
	int* distance;*/
	int startPoint;

	// The output array. dist[i] will hold the shortest
	// distance from src to i
	int* dist;

	// sptSet[i] will true if vertex i is included / in
	// shortest path tree or shortest distance from src to i
	// is finalized
	bool* sptSet;

	// Parent array to store shortest path tree
	int* parent;

	int amountOfIslands;

	std::vector<int> path;
};

#endif
