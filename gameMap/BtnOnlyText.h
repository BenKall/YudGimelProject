
#ifndef BTNONLYTEXT_H
#define BTNONLYTEXT_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Button.h"
#include "constants.h"
#include "AssetManager.h"

class BtnOnlyText :
	public Button
{
public:
	BtnOnlyText(float posX, float posY, int screenWidth, int screenHeight, sf::String btnString, SCREENTYPE& curScreen, SCREENTYPE toScreen);
	~BtnOnlyText();
	//Modifiers
	bool CheckMouse(sf::Vector2f* mousePosView);
	bool OnMouseHover(sf::Vector2f* mousePosView);
	bool OnMouseClick();
	bool isMouseClicked();
private:
	SCREENTYPE* curScreen;
	SCREENTYPE toScreen;

	float* btnWidthScale = new float(0.3f);
	float* btnHeightScale = new float(0.1f);
	float* btnTextScale = new float(0.05f);
	sf::Color* btnTextColor = new sf::Color(20.f, 160.f, 255.f);
	sf::Color* btnTextHoverColor = new sf::Color(255.f, 100.f, 50.f);
	sf::Font* btnFont = new sf::Font(AssetManager::GetFont("Assets/Fonts/BebasNeue-Regular.ttf"));
	float* btnTextOutlineScale = new float(0.01f);
	sf::Color* btnTextOutlineColor = new sf::Color(sf::Color::Black);
	sf::Color* btnFillColor = new sf::Color(sf::Color::Transparent);
};

#endif
