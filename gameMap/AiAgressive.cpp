#include "AiAgressive.h"

AiAgressive::AiAgressive(Level mapLayout) : AiEnemy (mapLayout)
{
	this->mapLayout = mapLayout;
}

std::vector<AntBuildParameters> AiAgressive::Think(Level curMapStatus)
{
	std::vector<AntBuildParameters> decision;
	this->mapLayout = curMapStatus;
	int amountOfIslands = this->mapLayout.size;
	for (size_t i = 0; i < amountOfIslands; i++)
	{
		if (this->mapLayout.islands[i]->GetStatus() == CONTROLOFENEMY)
		{
			if (this->mapLayout.islands[i]->GetAntsContained() > 10)
			{
				for (int j = 0; j < amountOfIslands; j++)
				{
					if (this->mapLayout.bridgesCoordinates[i][j] > 0 ||
						this->mapLayout.bridgesCoordinates[j][i] > 0)
					{
						AntBuildParameters tmpAntParams;
						if (this->mapLayout.bridgesCoordinates[i][j] > 0)
						{
							tmpAntParams.startCoordinate = i;
							tmpAntParams.endCoordinate = j;
							tmpAntParams.weight = this->mapLayout.bridgesCoordinates[i][j];
						}
						else
						{
							tmpAntParams.startCoordinate = i;
							tmpAntParams.endCoordinate = j;
							tmpAntParams.weight = this->mapLayout.bridgesCoordinates[j][i];
						}
						decision.push_back(tmpAntParams);
					}

				}
			}
		}
	}

	return decision;
}
