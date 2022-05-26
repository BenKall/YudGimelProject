#include "AiDijkstra.h"

AiDijkstra::AiDijkstra(Level mapLayout) : AiEnemy(mapLayout)
{
	this->mapLayout = mapLayout;
	this->amountOfIslands = this->mapLayout.size;
	
	int startingPoint = 0;
	for (int i = 0; i < this->amountOfIslands; i++)
	{
		if (this->mapLayout.islands[i]->GetStatus() == CONTROLOFENEMY)
			startingPoint = i;
	}
	dijkstra(startingPoint);

	int endPoint = this->amountOfIslands - 1;
	for (int i = 0; i < this->amountOfIslands; i++)
	{
		if (this->mapLayout.islands[i]->GetStatus() == CONTROLOFPLAYER)
			endPoint = i;
	}

	printf("\n\n\n\n\n\n\n");


	setPath(this->parent, endPoint);

	std::reverse(this->path.begin(), this->path.end());

	this->path.push_back(endPoint);

	//print path
	for (auto curPoint : this->path)
	{
		printf("\n%d ", curPoint );
	}
}

std::vector<AntBuildParameters> AiDijkstra::Think(Level curMapStatus)
{
	this->mapLayout = curMapStatus;
	std::vector<AntBuildParameters> decision;
	int toNextPoint = this->path.front();
	int lastInControlPoint = 0;
	int counter = 0;
	for (int i = 0; i < this->path.size(); i++)
	{
		if (this->mapLayout.islands[this->path.at(i)]->GetStatus() == CONTROLOFENEMY)
		{
			//toNextPoint = this->path.at(curPoint);
			lastInControlPoint = i;
		}

	}
	/*for (auto curPoint : this->path)
	{
		if (this->mapLayout.islands[curPoint]->GetStatus() == CONTROLOFENEMY)
		{
			toNextPoint = this->path.at(curPoint);
			lastInControlPoint = curPoint;
		}
	}*/
	if (this->path.at(lastInControlPoint) == this->path.at(this->path.size()-1))
	{
		printf("\nDone\n");
		//got to the point
	}
	else
	{
		while (lastInControlPoint + 1 != counter)
		{
			if (this->mapLayout.islands[this->path.at(counter)]->GetAntsContained() > 16)
			{
				AntBuildParameters tmpAntParams;
				int i = this->path.at(counter);
				int j = this->path.at(counter + 1);
				tmpAntParams.startCoordinate = i;
				tmpAntParams.endCoordinate = j;
				if (this->mapLayout.bridgesCoordinates[i][j] > 0)
					tmpAntParams.weight = this->mapLayout.bridgesCoordinates[i][j];
				else
					tmpAntParams.weight = this->mapLayout.bridgesCoordinates[j][i];
				decision.push_back(tmpAntParams);
			}
			counter++;
		}
	}
	return decision;
}

// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
// Initialize min value
int AiDijkstra::minDistance(int * dist, bool * sptSet)
{
	int min = INT_MAX, min_index;
	for (int i = 0; i < this->amountOfIslands; i++)
		if (sptSet[i] == false && dist[i] <= min)
			min = dist[i], min_index = i;
	return min_index;

}

// A utility function to print the constructed distance
	// array
int AiDijkstra::printSolution(int* dist, int* parent)
{
	int src = 0;
	printf("Vertex\t Distance\tPath");
	//cout << "Vertex\t Distance\tPath";
	for (int i = 1; i < this->amountOfIslands; i++) {
		printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i],
			src);
		printPath(parent, i);
	}
	return 0;
}



// Function to print shortest path from source to j using
// parent array
void AiDijkstra::printPath(int* parent, int j)
{
	// Base Case : If j is source
	if (parent[j] == -1)
		return;
	printPath(parent, parent[j]);
	printf("%d ", j);
	//cout << j << " ";
}

void AiDijkstra::dijkstra(int src)
{
	// The output array. dist[i] will hold the shortest
		// distance from src to i
	this->dist = (int*)calloc(sizeof(int), this->amountOfIslands);

	for (int i = 0; i < this->amountOfIslands; i++)
		this->dist[i] = INT_MAX;

	// sptSet[i] will true if vertex i is included / in
	// shortest path tree or shortest distance from src to i
	// is finalized
	this->sptSet = (bool*)calloc(sizeof(bool), this->amountOfIslands);
	for (int i = 0; i < this->amountOfIslands; i++)
		this->sptSet[i] = false;
	// Parent array to store shortest path tree
	this->parent = (int*)calloc(sizeof(int), this->amountOfIslands);
	// Initialize all distances as INFINITE
	for (int i = 0; i < this->amountOfIslands; i++)
		this->parent[i] = -1;

	// Distance of source vertex from itself is always 0
	this->dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < this->amountOfIslands - 1; count++) {
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to
		// src in first iteration.
		int u = minDistance(this->dist, this->sptSet);
		// Mark the picked vertex as processed
		sptSet[u] = true;
		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < this->amountOfIslands; v++)
		{
			// Update dist[v] only if is not in sptSet,
			// there is an edge from u to v, and total
			// weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (this->mapLayout.bridgesCoordinates[u][v] > 0)
			{
				if (!this->sptSet[v] && this->mapLayout.bridgesCoordinates[u][v]
					&& this->dist[u] + this->mapLayout.bridgesCoordinates[u][v] < this->dist[v]) {
					this->parent[v] = u;
					this->dist[v] = this->dist[u] + this->mapLayout.bridgesCoordinates[u][v];
				}
			}

			if (this->mapLayout.bridgesCoordinates[v][u] > 0)
			{
				if (!this->sptSet[v] && this->mapLayout.bridgesCoordinates[v][u]
					&& this->dist[u] + this->mapLayout.bridgesCoordinates[v][u] < this->dist[v]) {
					this->parent[v] = u;
					this->dist[v] = this->dist[u] + this->mapLayout.bridgesCoordinates[v][u];
				}
			}
		}
	}
	// print the constructed distance array
	printSolution(dist, parent);
}

void AiDijkstra::setPath(int * parent, int j)
{
	// Base Case : If j is source
	if (parent[j] == -1)
		return;
	this->path.push_back(parent[j]);
	setPath(parent, parent[j]);
	printf("%d ", j);
	//cout << j << " ";
}
