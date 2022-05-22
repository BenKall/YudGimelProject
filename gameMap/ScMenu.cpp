#include "ScMenu.h"

ScMenu::ScMenu(sf::RenderWindow * window, SCREENTYPE& curScreen) : Screen(window, curScreen)
{
	this->window = window;
	this->curScreen = curScreen;
	this->backgroundSprite = new sf::Sprite(AssetManager::GetTexture("Assets/Textures/antWarsBackground.png"));
	this->backgroundSprite->setScale(
		window->getSize().x / this->backgroundSprite->getGlobalBounds().width,
		window->getSize().y / this->backgroundSprite->getGlobalBounds().height
	);

	//this->curScreen = EXIT;

	BtnOnlyText* btn;
	btn = new BtnOnlyText(0.5f, 0.4f, window->getSize().x, window->getSize().y, "Play", curScreen, GAMESELECT);
	this->buttons.push_back(btn);
	btn = new BtnOnlyText(0.5f, 0.5f, window->getSize().x, window->getSize().y, "Credits", curScreen, CREDITS);
	this->buttons.push_back(btn);
	btn = new BtnOnlyText(0.5f, 0.6f, window->getSize().x, window->getSize().y, "Close", curScreen, EXIT);
	this->buttons.push_back(btn);
}

ScMenu::~ScMenu()
{
	for (auto *btn : this->buttons)
	{
		delete btn;
	}
	delete this->backgroundSprite;
	delete this->mousePos;
	delete this->mousePosView;
}

void ScMenu::UpdateElements()
{
	for (auto *btn : this->buttons)
	{
		btn->CheckMouse(this->mousePosView);
		
		if (this == this)
		{
			printf("%d\n", 100);
		}
	}
}

void ScMenu::Render()
{
	this->window->clear();
	this->window->draw(*this->backgroundSprite);
	for (auto *btn : this->buttons)
	{
		btn->Render(*(this->window));
	}
	this->window->display();
}

