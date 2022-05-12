#ifndef SCMENU_H
#define SCMENU_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Screen.h"
#include "BtnMenu.h"
class ScMenu :
	public Screen
{
public:
	ScMenu(sf::RenderWindow* window);
	void Update();
	void Render();
	void Start();
private:
	//Screen screen;

};

#endif
