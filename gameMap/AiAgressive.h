#ifndef AIAGGRESIVE_H
#define AIAGGRESIVE_H

#include "AiEnemy.h"
class AiAgressive :
	public AiEnemy
{
public:
	AiAgressive(Level mapLayout);
	std::vector<AntBuildParameters> Think(Level curMapStatus);
};

#endif

