#include "BtnOnlyText.h"

BtnOnlyText::BtnOnlyText(float posX, float posY, int screenWidth, int screenHeight, sf::String btnString, SCREENTYPE& curScreen, SCREENTYPE toScreen) : Button()
{
	//curScreen = EXIT;

	this->curScreen = &curScreen;
	this->toScreen = toScreen;

	//Menu button properties
	//Shape

	//Set Postion
	this->btnShape.setPosition(
		posX * screenWidth,
		posY * screenHeight
	);

	this->btnShape.setSize(sf::Vector2f(*this->widthScale * screenWidth, *this->heightScale * screenHeight));
	this->btnShape.setFillColor(*this->fillColor);

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
		(this->btnText.getLocalBounds().height) / 2 + this->btnText.getCharacterSize() / 2
	);
}

BtnOnlyText::~BtnOnlyText()
{
	delete this->widthScale;
	delete this->heightScale;
	delete this->textScale;
	delete this->textColor;
	delete this->textHoverColor;
	delete this->font;
	delete this->textOutlineScale;
	delete this->textOutlineColor;
	delete this->fillColor;
}

bool BtnOnlyText::CheckMouse(sf::Vector2f* mousePosView)
{
	return OnMouseHover(mousePosView);
}

//If mouse is on the button the color changes
bool BtnOnlyText::OnMouseHover(sf::Vector2f* mousePosView)
{
	bool flag = false;
	if (this->btnText.getGlobalBounds().contains(*mousePosView))
	{
		this->btnText.setFillColor(*textHoverColor);
		if(OnMouseClick())
			flag = true;
	}
	else
		this->btnText.setFillColor(*textColor);
	return flag;
}

bool BtnOnlyText::OnMouseClick()
{
	if (isMouseClicked())
	{
		*this->curScreen = toScreen;
		return true;
	}
	return false;
}

bool BtnOnlyText::isMouseClicked()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

SCREENTYPE BtnOnlyText::getToScreen()
{
	return this->toScreen;
}
