#include "ScLevelSelect.h"

ScLevelSelect::ScLevelSelect(sf::RenderWindow * window, SCREENTYPE & curScreen) : Screen(window, curScreen)
{
	this->window = window;
	this->backgroundSprite = new sf::Sprite(AssetManager::GetTexture("Assets/Textures/antWarsBackground.png"));
	this->backgroundSprite->setScale(
		window->getSize().x / this->backgroundSprite->getGlobalBounds().width,
		window->getSize().y / this->backgroundSprite->getGlobalBounds().height
	);

	//this->curScreen = EXIT;

	BtnClick* btnClick;
	BtnOnlyText* btnTxt;
	btnClick = new BtnClick(0.4f, 0.4f, window->getSize().x, window->getSize().y, "Level 1");
	this->lvlButtons.push_back(btnClick);
	this->lvlClicked.push_back(0);
	btnClick = new BtnClick(0.6f, 0.4f, window->getSize().x, window->getSize().y, "Level 2");
	this->lvlButtons.push_back(btnClick);
	this->lvlClicked.push_back(0);

	btnClick = new BtnClick(0.4f, 0.6f, window->getSize().x, window->getSize().y, "Ai 1");
	this->aiButtons.push_back(btnClick);
	this->aiClicked.push_back(0);
	btnClick = new BtnClick(0.6f, 0.6f, window->getSize().x, window->getSize().y, "Ai 2");
	this->aiButtons.push_back(btnClick);
	this->aiClicked.push_back(0);
	btnTxt = new BtnOnlyText(0.05f, 0.06f, window->getSize().x, window->getSize().y, "Back", curScreen, MENU);
	this->txtButtons.push_back(btnTxt);
	btnTxt = new BtnOnlyText(0.8f, 0.5f, window->getSize().x, window->getSize().y, "Start", curScreen, GAME);
	this->txtButtons.push_back(btnTxt);
	/*btn = new BtnOnlyText(0.5f, 0.6f, window->getSize().x, window->getSize().y, "Close", curScreen, EXIT);
	this->buttons.push_back(btn);*/
}

ScLevelSelect::~ScLevelSelect()
{
	for (auto *btn : this->lvlButtons)
	{
		delete btn;
	}
	for (auto *btn : this->aiButtons)
	{
		delete btn;
	}
	for (auto *btn : this->txtButtons)
	{
		delete btn;
	}
	delete this->backgroundSprite;
	delete this->mousePos;
	delete this->mousePosView;
}

//Update buttons and make sure only one level button and one ai button is picked
void ScLevelSelect::UpdateElements()
{
	bool flagLvlClicked = false;
	for (int i = 0; i < lvlClicked.size(); i++)
	{
		if (lvlClicked.at(i) == 1)
			flagLvlClicked = true;
	}
	for (int i = 0; i < lvlButtons.size(); i++)
	{
		if (lvlButtons.at(i)->CheckMouse(this->mousePosView))
		{
			if (!flagLvlClicked || lvlClicked.at(i) == 1)
			{
				if (lvlButtons.at(i)->isButtonClicked())
					lvlClicked.at(i) = 1;
				else
					lvlClicked.at(i) = 0;
				
			}
			else
				lvlButtons.at(i)->clickButton();
		}
	}
	bool flagAiClicked = false;
	for (int i = 0; i < aiClicked.size(); i++)
	{
		if (aiClicked.at(i) == 1)
			flagAiClicked = true;
	}
	for (int i = 0; i < aiButtons.size(); i++)
	{
		if (aiButtons.at(i)->CheckMouse(this->mousePosView))
		{
			if (!flagAiClicked || aiClicked.at(i) == 1)
			{
				if (aiButtons.at(i)->isButtonClicked())
					aiClicked.at(i) = 1;
				else
					aiClicked.at(i) = 0;

			}
			else
				aiButtons.at(i)->clickButton();
		}
	}

	for (auto *btn : this->txtButtons)
	{
		if (btn->CheckMouse(this->mousePosView))
		{
			if(btn->getToScreen() == MENU)
				Reset();// if this was clicked it need to clear the data, set it to initial values
			if (btn->getToScreen() == GAME)
			{
				if (flagAiClicked && flagLvlClicked)
				{
					Reset();
				}
				else
				{
					curScreen = GAMESELECT;
				}
			}
		}
	}
}

void ScLevelSelect::Render()
{
	this->window->clear();
	this->window->draw(*this->backgroundSprite);
	for (auto *btn : this->lvlButtons)
	{
		btn->Render(*(this->window));
	}
	for (auto *btn : this->aiButtons)
	{
		btn->Render(*(this->window));
	}
	for (auto *btn : this->txtButtons)
	{
		btn->Render(*(this->window));
	}
	this->window->display();
}

//Reset vectors
void ScLevelSelect::Reset()
{
	for (int i = 0; i < lvlClicked.size(); i++)
	{
		if (lvlClicked.at(i) == 1)
			lvlButtons.at(i)->clickButton();
		lvlClicked.at(i) = 0;
	}
	for (int i = 0; i < aiClicked.size(); i++)
	{
		if (aiClicked.at(i) == 1)
			aiButtons.at(i)->clickButton();
		aiClicked.at(i) = 0;
	}
}
