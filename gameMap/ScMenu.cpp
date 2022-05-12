#include "ScMenu.h"

ScMenu::ScMenu(sf::RenderWindow * window) : Screen(window)
{
	this->window = window;

	BtnMenu* btn;
	btn = new BtnMenu(0.5f, 0.5f, window->getSize().x, window->getSize().y, "Play");
	this->buttons.push_back(btn);
	btn = new BtnMenu(0.5f, 0.7f, window->getSize().x, window->getSize().y, "Options");
	this->buttons.push_back(btn);
}

void ScMenu::Update()
{
}

void ScMenu::Render()
{
	this->window->clear();
	for (auto *btn : this->buttons)
	{
		btn->Render(*(this->window));
	}
	this->window->display();

}

void ScMenu::Start()
{
	Run();
}
