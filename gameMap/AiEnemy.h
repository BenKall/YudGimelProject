#ifndef AIENEMY_H
#define AIENEMY_H


#include<SFML/Graphics.hpp>
#include<iostream>
#include "CustomStructs.h"
#include "Constants.h"
#include "Ant.h"

class AiEnemy
{
public:
	AiEnemy(Level curLevel);

	std::vector<AntBuildParameters> Think(Level curMapStatus, std::vector<AntBuildParameters>(*curAi)(Level));

	static std::vector<AntBuildParameters> AiAgressive(Level curMapStatus);
	static std::vector<AntBuildParameters> AiDijkstra(Level curMapStatus);

private:
	Level mapLayout;
};

#endif