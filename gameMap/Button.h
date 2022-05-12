#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "constants.h"
#include "AssetManager.h"

class Button
{
public:
	Button() {};

	void Render(sf::RenderTarget & target)
	{
		target.draw(this->btnShape);
		target.draw(this->btnText);

		printf("%s \n", btnText.getString());
		printf("%f \n", btnText.getOutlineThickness());
		printf("%f \n", btnShape.getSize().x);
	}

protected:
	sf::RectangleShape btnShape;
	sf::Text btnText;

	//float btnWidthScale = 0.3f;
	//float btnHeightScale = 0.1f;
	//float btnOutlineThicknessScale;
	//sf::Color btnOutlineColor;
	//sf::Color btnFillColor = sf::Color::Transparent;

	//float btnTextScale = 0.05f;
	//sf::Color btnTextColor = sf::Color(20.f, 200.f, 80.f);
	//sf::String btnTextString;
	//sf::Font btnFont = AssetManager::GetFont("Assets/Fonts/space age.ttf");;
	//float btnTextOutlineScale = 0.01f;
	//sf::Color btnTextOutlineColor;
};

#endif
