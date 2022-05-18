#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Screen.h"
#include "constants.h"
#include "AssetManager.h"

class Button
{
public:
	Button() {};

	const sf::Text GetText() const {
		return this->btnText;
	};

	const sf::RectangleShape GetShape() const {
		return this->btnShape;
	};

	//Modifiers
	virtual bool CheckMouse(sf::Vector2f* mousePosView) = 0;

	void Render(sf::RenderTarget & target)
	{
		target.draw(this->btnShape);
		target.draw(this->btnText);
	}

protected:
	sf::RectangleShape btnShape;
	sf::Text btnText;
	Screen* btnCurScreen;
	Screen* btnToScreen;
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
