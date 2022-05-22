
#ifndef BTNCLICK_H
#define BTNCLICK_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Button.h"
#include "constants.h"
#include "AssetManager.h"

class BtnClick :
	public Button
{
public:
	BtnClick(float posX, float posY, int screenWidth, int screenHeight, sf::String btnString);
	~BtnClick();
	//Modifiers
	bool CheckMouse(sf::Vector2f* mousePosView);
	bool OnMouseHover(sf::Vector2f* mousePosView);
	bool OnMouseClick();
	bool isMouseClicked();
	void clickButton();

	//Accesor
	bool isButtonClicked();
private:
	bool* isClicked = new bool(false);
	bool* mousePressed = new bool(false);

	float* widthScale = new float(0.15f);
	float* heightScale = new float(0.1f);
	float* textScale = new float(0.05f);
	sf::Color* textColor = new sf::Color(20.f, 160.f, 255.f);
	sf::Color* textClickColor = new sf::Color(50.f, 200.f, 50.f);
	sf::Font* font = new sf::Font(AssetManager::GetFont("Assets/Fonts/BebasNeue-Regular.ttf"));
	float* textOutlineScale = new float(0.01f);
	sf::Color* textOutlineColor = new sf::Color(sf::Color::Black);
	sf::Color* shapeOutlineColor = new sf::Color(sf::Color::Black);
	sf::Color* shapeOutlineClickedColor = new sf::Color(50.f, 200.f, 50.f);
	float* shapeOutlineScale = new float(0.01f);
	sf::Texture* texture = new sf::Texture(AssetManager::GetTexture("Assets/Textures/grayTex.png"));
	//this->shape.setTexture(&ilTexture);
};

#endif