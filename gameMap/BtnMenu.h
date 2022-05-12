
#ifndef BTNMENU_H
#define BTNMENU_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Button.h"
#include "constants.h"
#include "AssetManager.h"

class BtnMenu :
	public Button
{
public:
	BtnMenu(float posX, float posY, int screenWidth, int screenHeight, sf::String btnString);
private:
	float btnWidthScale = 0.3f;
	float btnHeightScale = 0.1f;
	float btnTextScale = 0.05f;
	sf::Color btnTextColor = sf::Color(20.f, 200.f, 80.f);
	sf::Font btnFont = AssetManager::GetFont("Assets/Fonts/space age.ttf");;
	float btnTextOutlineScale = 0.01f;
	sf::Color btnTextOutlineColor = sf::Color::Black;
	sf::Color btnFillColor = sf::Color::Transparent;
};

#endif
