#ifndef SCMENU_H
#define SCMENU_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include <typeinfo>
#include "Screen.h"
#include "BtnOnlyText.h"
class ScMenu :
	public Screen
{
public:
	ScMenu(sf::RenderWindow* window, SCREENTYPE& curScreen);
	virtual ~ScMenu();
	void UpdateElements();
	void Render();
private:
	SCREENTYPE& curScreen = *new SCREENTYPE(MENU);
	std::vector<Button*> buttons;
};

#endif
