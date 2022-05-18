#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ScMenu.h"
#include "AssetManager.h"
#include <iostream>

int main()
{
	AssetManager manager;

	//Game game;

	//game.run();

	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(SCREENW, SCREENH), "Ant Wars", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(FRAMERATE);
	window->setVerticalSyncEnabled(false);

	SCREENTYPE curScreen = MENU;
	ScMenu* scMenu = new ScMenu(window, curScreen);
	ScCredits* scCredits = new ScCredits(window, curScreen);
	std::vector<Screen*> allScreens;
	allScreens.push_back(scMenu);
	allScreens.push_back(scCredits);
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
