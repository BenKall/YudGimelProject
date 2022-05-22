#include "ScCredits.h"

ScCredits::ScCredits(sf::RenderWindow * window, SCREENTYPE& curScreen) : Screen(window, curScreen)
{
	this->window = window;
	this->backgroundSprite = new sf::Sprite(AssetManager::GetTexture("Assets/Textures/antWarsBackground.png"));
	this->backgroundSprite->setScale(
		window->getSize().x / this->backgroundSprite->getGlobalBounds().width,
		window->getSize().y / this->backgroundSprite->getGlobalBounds().height
	);

	this->creatorName.setPosition(
		*this->textRelativeX * this->window->getSize().x,
		*this->textRelativeY * this->window->getSize().y
	);

	this->creatorName.setString(*this->textString);
	this->creatorName.setCharacterSize(*this->textScale * this->window->getSize().y);
	this->creatorName.setFont(*this->font);
	this->creatorName.setOutlineThickness(*this->textOutlineScale * this->window->getSize().y);
	this->creatorName.setOutlineColor(*this->textOutlineColor);
	this->creatorName.setFillColor(*this->textColor);

	this->creatorName.setOrigin(
		this->creatorName.getLocalBounds().width / 2,
		(this->creatorName.getLocalBounds().height) / 2 + this->creatorName.getCharacterSize() / 2
	);

	BtnOnlyText* btn;
	btn = new BtnOnlyText(0.05f, 0.06f, window->getSize().x, window->getSize().y, "Back", curScreen, MENU);
	this->buttons.push_back(btn);
}

void ScCredits::UpdateElements()
{
	for (auto *btn : this->buttons)
	{
		/*if (*/ btn->CheckMouse(this->mousePosView); /*&& btn->GetText().getString() == "Close")*/
		//{
		//	//delete this;
		//	exit(1);
		//	//this->window->close();
		//}

		////std::cout << typeid(btn).name() << std::endl;
		///*if (typeid(btn).name() == "BtnOnlyText")
		//{

		//}*/
	}
}

void ScCredits::Render()
{
	this->window->clear();
	this->window->draw(*this->backgroundSprite);
	this->window->draw(this->creatorName);
	for (auto *btn : this->buttons)
	{
		btn->Render(*(this->window));
	}
	this->window->display();
}