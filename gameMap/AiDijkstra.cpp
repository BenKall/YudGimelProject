#include "AiDijkstra.h"

AiDijkstra::AiDijkstra(Level mapLayout) : AiEnemy(mapLayout)
{
	int ilNum = mapLayout.size;
	
		//Preperation
		adj = (std::list<GraphPoint>*)calloc(sizeof(std::list<GraphPoint>), ilNum);
	
		////Not necessery?
		//std::list <GraphPoint> tmpGp;
		//for (int i = 0; i < ilNum; i++)
		//{
		//	adj[i].begin;
		//}
	
		//Create Adjency Lists
		for (int i = 0; i < ilNum; i++)
		{
			for (int j = 0; j < ilNum; j++)
			{
				if (mapLayout.bridgesCoordinates[i][j] > 0 ||
					mapLayout.bridgesCoordinates[j][i] > 0)
				{
					GraphPoint tmpGp;
					tmpGp.num = j;
					if (mapLayout.bridgesCoordinates[i][j] > 0)
						tmpGp.weight = mapLayout.bridgesCoordinates[i][j];
					else
						tmpGp.weight = mapLayout.bridgesCoordinates[j][i];
	
					adj[i].push_back(tmpGp);
				}
				
			}
		}
	
		//find starting node
		startPoint = 0;
		for (int i = 0; i < ilNum; i++)
		{
			if (mapLayout.islands[i]->GetStatus() == CONTROLOFENEMY)
				startPoint = i;
		}
	
		////Queue
		std::priority_queue<GraphPoint> q;
	
		processed = (int*)calloc(sizeof(int), ilNum);
		distance = (int*)calloc(sizeof(int), ilNum);
	
		//Dijkstra
		for (int i = 1; i <= ilNum; i++) distance[i] = INF;
		distance[startPoint] = 0;
		GraphPoint tmp;
		tmp.num = startPoint;
		tmp.weight = 0;
		q.push(tmp);
		while (!q.empty()) {
			int a = q.top().num; q.pop(); //int a = q.top().second; q.pop();
			if (processed[a]) continue;
			processed[a] = 1; // = true
			for (auto u : adj[a]) {
				int b = u.num, w = u.weight; //int b = u.first, w = u.second;
				if (distance[a] + w < distance[b]) {
					distance[b] = distance[a] + w;
					tmp.num = b;
					tmp.weight = -distance[b];
					q.push(tmp); //q.push({ -distance[b], b });
				}
			}
		}
		

		for (int i = 0; i < adj->size(); i++)
		{
			for (auto u : adj[i])
			{
				std::cout << u.num + ", " + u.weight << std::endl;
			}
		}
		
		/*for (auto u : proce)
		{
			std::cout << u.num + "," + u.weight << std::endl;
		}*/

		//return std::vector<AntBuildParameters>();
}

std::vector<AntBuildParameters> AiDijkstra::Think(Level curMapStatus)
{
	return std::vector<AntBuildParameters>();
}
