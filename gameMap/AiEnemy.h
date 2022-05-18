#ifndef AIENEMY_H
#define AIENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include<list>
#include<queue>
#include "CustomStructs.h"
#include "Constants.h"
#include "Ant.h"

class AiEnemy
{
public:
	AiEnemy(Level curLevel);

	virtual std::vector<AntBuildParameters> Think(Level curMapStatus) = 0;


protected:
	Level mapLayout;

};

#endif