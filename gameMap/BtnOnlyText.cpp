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

	this->btnShape.setSize(sf::Vector2f(*this->btnWidthScale * screenWidth, *this->btnHeightScale * screenHeight));
	this->btnShape.setFillColor(*this->btnFillColor);

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
	this->btnText.setCharacterSize(*this->btnTextScale * screenHeight);
	this->btnText.setFont(*this->btnFont);
	this->btnText.setOutlineThickness(*this->btnTextOutlineScale * screenHeight);
	this->btnText.setOutlineColor(*this->btnTextOutlineColor);
	this->btnText.setFillColor(*this->btnTextColor);

	this->btnText.setOrigin(
		this->btnText.getLocalBounds().width / 2,
		(this->btnText.getLocalBounds().height) / 2 + this->btnText.getCharacterSize() / 2
	);
}

BtnOnlyText::~BtnOnlyText()
{
	delete this->btnWidthScale;
	delete this->btnHeightScale;
	delete this->btnTextScale;
	delete this->btnTextColor;
	delete this->btnTextHoverColor;
	delete this->btnFont;
	delete this->btnTextOutlineScale;
	delete this->btnTextOutlineColor;
	delete this->btnFillColor;
}

bool BtnOnlyText::CheckMouse(sf::Vector2f* mousePosView)
{
	return OnMouseHover(mousePosView);
}

bool BtnOnlyText::OnMouseHover(sf::Vector2f* mousePosView)
{
	bool flag = false;
	if (this->btnText.getGlobalBounds().contains(*mousePosView))
	{
		this->btnText.setFillColor(*btnTextHoverColor);
		if(OnMouseClick())
			flag = true;
	}
	else
		this->btnText.setFillColor(*btnTextColor);
	return flag;
}

bool BtnOnlyText::OnMouseClick()
{
	if (isMouseClicked())
	{
		*this->curScreen = toScreen;
		//if (btnCurScreen == btnToScreen)
		//{
		//	return true;
		//	//delete btnCurScreen;
		//}
		//else
		//this->btnToScreen->Run();
	}
	return false;
}

bool BtnOnlyText::isMouseClicked()
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
