#include "BtnMenu.h"

BtnMenu::BtnMenu(float posX, float posY, int screenWidth, int screenHeight, sf::String btnString) : Button()
{
	
	
	//Menu button properties
	//Shape

	//Set Postion
	this->btnShape.setPosition(
		posX * screenWidth,
		posY * screenHeight
	);

	this->btnShape.setSize(sf::Vector2f(btnWidthScale * screenWidth, btnHeightScale * screenHeight));
	this->btnShape.setFillColor(btnFillColor);
	this->btnShape.setOutlineColor(sf::Color::White);
	this->btnShape.setOutlineThickness(5.f);
	
	//Text

	this->btnText.setString(btnString);
	this->btnText.setCharacterSize(btnTextScale * screenHeight);
	this->btnText.setFont(btnFont);
	this->btnText.setOutlineThickness(btnTextOutlineScale * screenHeight);
	this->btnText.setOutlineColor(btnTextOutlineColor);

	this->btnText.setPosition(
		this->btnShape.getPosition().x + this->btnShape.getLocalBounds().width / 2,
		this->btnShape.getPosition().y + this->btnShape.getLocalBounds().height / 2
	);

	this->btnText.setOrigin(
		btnText.getLocalBounds().width / 2,
		(btnText.getLocalBounds().height) / 2 + btnText.getCharacterSize() / 2
	);
}
