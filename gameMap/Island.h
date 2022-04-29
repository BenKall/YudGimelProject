#ifndef ISLAND_H
#define ISLAND_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "constants.h"
#include "AssetManager.h"

class Island
{
public:
	Island(sf::Vector2f pos, int antsContained, ISLANDSTATUS status);

	const sf::FloatRect GetBounds() const;

	void DivideAntsContained();
	void ChangeAntsContained(int amount, ISLANDSTATUS status);

	void SetText(int newNumber);
	void SetPosRelativeToScreen(int screenWidth, int screenHeight);

	//Accessor
	const sf::Vector2f& GetPos() const;
	const sf::CircleShape getShape() const;
	const sf::Color GetOutlineColor() const;
	const int& GetAntsContained() const;
	const ISLANDSTATUS& GetStatus() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void SetOutlineColor(const sf::Color color);
	void SetAntsContained(const sf::Color color);
	void SetStatusColors(ISLANDSTATUS status);

	void Render(sf::RenderWindow& target);

private:
	sf::CircleShape ilShape;
	sf::Text ilText;
	sf::Font ilFont;
	sf::Texture ilTexture;
	//Who is in control of the island
	ISLANDSTATUS status;
	int antsContained;
};

#endif

