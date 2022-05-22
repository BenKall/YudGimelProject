#ifndef SCLEVELSELECT_H
#define SCLEVELSELECT_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include <typeinfo>
#include <list>
#include "Screen.h"
#include "ScCredits.h"
#include "BtnOnlyText.h"
#include "BtnClick.h"
class ScLevelSelect :
	public Screen
{
public:
	ScLevelSelect(sf::RenderWindow* window, SCREENTYPE& curScreen);
	virtual ~ScLevelSelect();
	void UpdateElements();
	void Render();
	void Reset();
private:
	std::vector<BtnClick*> lvlButtons;
	std::vector<BtnClick*> aiButtons;
	std::vector<BtnOnlyText*> txtButtons;
	std::vector<int> lvlClicked;
	std::vector<int> aiClicked;
};

#endif

