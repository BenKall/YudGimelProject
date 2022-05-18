#ifndef SCCREDITS_H
#define SCCREDITS_H
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include <typeinfo>
#include "Screen.h"
#include "BtnOnlyText.h"
class ScCredits :
	public Screen
{
public:
	ScCredits(sf::RenderWindow* window, SCREENTYPE& curScreen);
	void UpdateElements();
	void Render();
private:
	sf::Text creatorName;
	std::vector<Button*> buttons;

	float* textRelativeX = new float(0.5f);
	float* textRelativeY = new float(0.5f);
	sf::String* textString = new sf::String("Ben Kallush");
	float* textScale = new float(0.05f);
	sf::Color* textColor = new sf::Color(20.f, 160.f, 60.f);
	sf::Font* font = new sf::Font(AssetManager::GetFont("Assets/Fonts/MusticaPro-SemiBold.otf"));
	float* textOutlineScale = new float(0.005f);
	sf::Color* textOutlineColor = new sf::Color(sf::Color::Black);
};

#endif

