#include "AiEnemy.h"

AiEnemy::AiEnemy(Level curLevel)
{
	this->mapLayout = curLevel;
}

//std::vector<AntBuildParameters> AiEnemy::Think(Level curMapStatus, std::vector<AntBuildParameters>(*curAi)(Level))
//{
//	return curAi(curMapStatus);
//
//
//}
//
//std::vector<AntBuildParameters> AiEnemy::AiAgressive(Level curMapStatus)
//{
//	std::vector<AntBuildParameters> decision;
//	int amountOfIslands = curMapStatus.size;
//	for (size_t i = 0; i < amountOfIslands; i++)
//	{
//		if (curMapStatus.islands[i]->GetStatus() == CONTROLOFENEMY)
//		{
//			if (curMapStatus.islands[i]->GetAntsContained() > 10)
//			{
//				for (int j = 0; j < amountOfIslands; j++)
//				{
//					if (curMapStatus.bridgesCoordinates[i][j] > 0 ||
//						curMapStatus.bridgesCoordinates[j][i] > 0)
//					{
//						AntBuildParameters tmpAntParams;
//						if (curMapStatus.bridgesCoordinates[i][j] > 0)
//						{
//							tmpAntParams.startCoordinate = i;
//							tmpAntParams.endCoordinate = j;
//							tmpAntParams.weight = curMapStatus.bridgesCoordinates[i][j];
//						}
//						else
//						{
//							tmpAntParams.startCoordinate = i;
//							tmpAntParams.endCoordinate = j;
//							tmpAntParams.weight = curMapStatus.bridgesCoordinates[j][i];
//						}
//						decision.push_back(tmpAntParams);
//					}
//					
//				}
//			}
//		}
//	}
//
//	return decision;
//}
//
//std::vector<AntBuildParameters> AiEnemy::AiDijkstra(Level curMapStatus)
//{
//	int ilNum = curMapStatus.size;
//
//	//Preperation
//	std::list<GraphPoint>* adj = (std::list<GraphPoint>*)calloc(sizeof(std::list<GraphPoint>), ilNum);
//
//	//Not necessery?
//	/*std::list <GraphPoint> tmpGp;
//	for (int i = 0; i < curMapStatus.size; i++)
//	{
//		adj[i] = tmpGp;
//	}*/
//
//	//Create Adjency Lists
//	for (int i = 0; i < ilNum; i++)
//	{
//		for (int j = 0; j < ilNum; j++)
//		{
//			if (curMapStatus.bridgesCoordinates[i][j] > 0 ||
//				curMapStatus.bridgesCoordinates[j][i] > 0)
//			{
//				GraphPoint tmpGp;
//				tmpGp.num = j;
//				if (curMapStatus.bridgesCoordinates[i][j] > 0)
//					tmpGp.weight = curMapStatus.bridgesCoordinates[i][j];
//				else
//					tmpGp.weight = curMapStatus.bridgesCoordinates[j][i];
//
//				adj[i].push_back(tmpGp);
//			}
//			
//		}
//	}
//
//	//find starting node
//	int startPoint = 0;
//	for (int i = 0; i < ilNum; i++)
//	{
//		if (curMapStatus.islands[i]->GetStatus() == CONTROLOFENEMY)
//			startPoint = i;
//	}
//
//	////Queue
//	std::priority_queue<GraphPoint> q;
//
//	int* processed = (int*)calloc(sizeof(int), ilNum);
//	int* distance = (int*)calloc(sizeof(int), ilNum);
//
//	//Dijkstra
//	for (int i = 1; i <= ilNum; i++) distance[i] = INF;
//	distance[startPoint] = 0;
//	GraphPoint tmp;
//	tmp.num = startPoint;
//	tmp.weight = 0;
//	q.push(tmp);
//	while (!q.empty()) {
//		int a = q.top().num; q.pop(); //int a = q.top().second; q.pop();
//		if (processed[a]) continue;
//		processed[a] = 1; // = true
//		for (auto u : adj[a]) {
//			int b = u.num, w = u.weight; //int b = u.first, w = u.second;
//			if (distance[a] + w < distance[b]) {
//				distance[b] = distance[a] + w;
//				tmp.num = b;
//				tmp.weight = -distance[b];
//				q.push(tmp); //q.push({ -distance[b], b });
//			}
//		}
//	}
//
//	return std::vector<AntBuildParameters>();
//}
