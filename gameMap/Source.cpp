#include <SFML/Graphics.hpp>
#include "Game.h"
#include "AssetManager.h"
#include <iostream>

int main()
{
	AssetManager manager;

	Game game;

	game.run();

	return 0;
}
