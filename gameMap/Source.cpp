#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ScMenu.h"
#include "ScCredits.h"
#include "ScLevelSelect.h"
#include "AssetManager.h"
#include <iostream>

int main()
{
	AssetManager manager;

	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(SCREENW, SCREENH), "Ant Wars", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(FRAMERATE);
	window->setVerticalSyncEnabled(false);

	SCREENTYPE curScreen = MENU;

	//Game* game = new Game(window, curScreen, 3, 2);

	//curScreen = GAME;
	//while (curScreen == GAME)//(window->isOpen())
	//{
	//	game->Run();
	//}
	

	

	ScMenu* scMenu = new ScMenu(window, curScreen);
	ScCredits* scCredits = new ScCredits(window, curScreen);
	ScLevelSelect* scLevelSelect = new ScLevelSelect(window, curScreen);
	std::vector<Screen*> allScreens;
	allScreens.push_back(scMenu);
	allScreens.push_back(scCredits);
	allScreens.push_back(scLevelSelect);
	while (curScreen != EXIT)//(window->isOpen())
	{
		allScreens.at(curScreen)->Run();
	}
	for (auto sc : allScreens)
	{
		delete sc;
	}
	return 0;
}
