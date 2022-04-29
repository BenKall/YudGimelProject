#include "AiEnemy.h"

AiEnemy::AiEnemy(Level curLevel)
{
	this->mapLayout = curLevel;
}

std::vector<AntBuildParameters> AiEnemy::Think(Level curMapStatus, std::vector<AntBuildParameters>(*curAi)(Level))
{
	return curAi(curMapStatus);


}

std::vector<AntBuildParameters> AiEnemy::AiAgressive(Level curMapStatus)
{
	std::vector<AntBuildParameters> decision;
	int amountOfIslands = curMapStatus.size;
	for (size_t i = 0; i < amountOfIslands; i++)
	{
		if (curMapStatus.islands[i]->GetStatus() == CONTROLOFENEMY)
		{
			if (curMapStatus.islands[i]->GetAntsContained() > 10)
			{
				for (int j = 0; j < amountOfIslands; j++)
				{
					if (curMapStatus.bridgesCoordinates[i][j] > 0 ||
						curMapStatus.bridgesCoordinates[j][i] > 0)
					{
						AntBuildParameters tmpAntParams;
						if (curMapStatus.bridgesCoordinates[i][j] > 0)
						{
							tmpAntParams.startCoordinate = i;
							tmpAntParams.endCoordinate = j;
							tmpAntParams.weight = curMapStatus.bridgesCoordinates[i][j];
						}
						else
						{
							tmpAntParams.startCoordinate = i;
							tmpAntParams.endCoordinate = j;
							tmpAntParams.weight = curMapStatus.bridgesCoordinates[j][i];
						}
						decision.push_back(tmpAntParams);
					}
					
				}
			}
		}
	}

	return decision;
}

std::vector<AntBuildParameters> AiEnemy::AiDijkstra(Level curMapStatus)
{

	for (int i = 1; i <= n; i++) distance[i] = INF;
	distance[x] = 0;
	q.push({ 0,x });
	while (!q.empty()) {
		int a = q.top().second; q.pop();
		if (processed[a]) continue;
		processed[a] = true;
		for (auto u : adj[a]) {
			int b = u.first, w = u.second;
			if (distance[a] + w < distance[b]) {
				distance[b] = distance[a] + w;
				q.push({ -distance[b],b });
			}
		}
	}

	return std::vector<AntBuildParameters>();
}
