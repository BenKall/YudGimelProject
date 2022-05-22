#include "BtnClick.h"

BtnClick::BtnClick(float posX, float posY, int screenWidth, int screenHeight, sf::String btnString) : Button()
{
	//Menu button properties
	//Shape

	//Set Postion
	this->btnShape.setPosition(
		posX * screenWidth,
		posY * screenHeight
	);

	this->btnShape.setSize(sf::Vector2f(*this->widthScale * screenWidth, *this->heightScale * screenHeight));
	this->btnShape.setTexture(this->texture);
	this->btnShape.setOutlineColor(*this->shapeOutlineColor);
	this->btnShape.setOutlineThickness(*this->shapeOutlineScale * screenHeight);

	this->btnShape.setOrigin(
		this->btnShape.getLocalBounds().width / 2,
		(this->btnShape.getLocalBounds().height) / 2
	);

	//Text

	this->btnText.setPosition(
		this->btnShape.getPosition().x,
		this->btnShape.getPosition().y
	);

	this->btnText.setString(btnString);
	this->btnText.setCharacterSize(*this->textScale * screenHeight);
	this->btnText.setFont(*this->font);
	this->btnText.setOutlineThickness(*this->textOutlineScale * screenHeight);
	this->btnText.setOutlineColor(*this->textOutlineColor);
	this->btnText.setFillColor(*this->textColor);

	this->btnText.setOrigin(
		this->btnText.getLocalBounds().width / 2,
		(this->btnText.getLocalBounds().height) / 2 + this->btnText.getCharacterSize() / 4
	);
}

BtnClick::~BtnClick()
{
	delete this->widthScale;
	delete this->heightScale;
	delete this->textScale;
	delete this->textColor;
	delete this->textClickColor;
	delete this->font;
	delete this->textOutlineScale;
	delete this->textOutlineColor;
	delete this->texture;
}

bool BtnClick::CheckMouse(sf::Vector2f* mousePosView)
{
	return OnMouseHover(mousePosView);
}

bool BtnClick::OnMouseHover(sf::Vector2f* mousePosView)
{
	bool flag = false;
	if (this->btnShape.getGlobalBounds().contains(*mousePosView))
	{
		//this->btnText.setFillColor(*textHoverColor);
		if (OnMouseClick())
			flag = true;
	}
	else
		//this->btnText.setFillColor(*textColor);
	return flag;
}

//If mouse is clicked change the color of the button and set a Clicked flag
bool BtnClick::OnMouseClick()
{
	bool flag = false;
	if (isMouseClicked())
	{
		if (*this->mousePressed == false)
		{
			*this->mousePressed = true;
			flag = true;
			*isClicked = !*isClicked;
			if (*isClicked)
			{
				this->btnText.setFillColor(*this->textClickColor);
				this->btnShape.setOutlineColor(*this->shapeOutlineClickedColor);
			}
			else
			{
				this->btnText.setFillColor(*this->textColor);
				this->btnShape.setOutlineColor(*this->shapeOutlineColor);
			}
		}
	}
	else
	{
		*this->mousePressed = false;
	}
	return flag;
}

bool BtnClick::isMouseClicked()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

//This method clicks the button
void BtnClick::clickButton()
{
	*isClicked = !*isClicked;
	if (*isClicked)
	{
		this->btnText.setFillColor(*this->textClickColor);
		this->btnShape.setOutlineColor(*this->shapeOutlineClickedColor);
	}
	else
	{
		this->btnText.setFillColor(*this->textColor);
		this->btnShape.setOutlineColor(*this->shapeOutlineColor);
	}
}

bool BtnClick::isButtonClicked()
{
	return *this->isClicked;
}
