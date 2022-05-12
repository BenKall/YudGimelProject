#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Button.h"
#include "constants.h"
#include "AssetManager.h"

class Screen
{
public:
	Screen(sf::RenderWindow* window) { this->window = window; };

	//Virtual functions
	virtual void Update() = 0;
	virtual void Render() = 0;

	//Functions
	void UpdatePollEvents()
	{
		sf::Event e;
		while (this->window->pollEvent(e))
		{
			if (e.Event::type == sf::Event::Closed)
			{
				this->window->close();
			}
		}
	};

	void Run()
	{
		while (this->window->isOpen())
		{
			this->UpdatePollEvents();
			this->Update();
			this->Render();
		}
	}
protected:
	sf::RenderWindow* window;
	std::vector<Button*> buttons;
};
#endif
