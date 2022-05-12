#include <SFML/Graphics.hpp>
#include "Game.h"
#include "ScMenu.h"
#include "AssetManager.h"
#include <iostream>

int main()
{
	AssetManager manager;

	/*Game game;

	game.run();*/

	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(SCREENW, SCREENH), "Draw Circles", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(FRAMERATE);
	window->setVerticalSyncEnabled(false);

	ScMenu screen(window);
	screen.Start();
	return 0;
}
