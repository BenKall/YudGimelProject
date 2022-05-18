#ifndef SCREEN_H
#define SCREEN_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include <iostream>
#include "constants.h"
#include "AssetManager.h"

class Screen
{
public:

	Screen(sf::RenderWindow* window, SCREENTYPE& curScreen)
	{
		this->window = window;
		this->mousePos = new sf::Vector2i();
		this->mousePosView = new sf::Vector2f();
		this->backgroundSprite = new sf::Sprite();
		this->curScreen = curScreen;
	};

	virtual ~Screen() {
		//delete this->window;
		//delete this->backgroundSprite;
		//delete this->mousePos;
		//delete this->mousePosView;
	};

	void Update()
	{
		UpdateMouse();
		UpdateElements();
	};
	void UpdateMouse()
	{
		*this->mousePos = sf::Mouse::getPosition(*this->window);
		*this->mousePosView = this->window->mapPixelToCoords(*this->mousePos);
	};
		
	//Virtual functions
	virtual void UpdateElements() = 0;
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
		this->UpdatePollEvents();
		this->Update();
		this->Render();
	}
protected:
	sf::RenderWindow* window;
	sf::Sprite* backgroundSprite;

	sf::Vector2i* mousePos;
	sf::Vector2f* mousePosView;

	SCREENTYPE curScreen;
};
#endif
