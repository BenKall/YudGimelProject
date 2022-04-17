#ifndef BRIDGE_H
#define BRIDGE_H
#define _USE_MATH_DEFINES
#include<SFML/Graphics.hpp>
#include<iostream>
#include <math.h>
#include "AssetManager.h"
#include "UsefulFunctions.h"

class Bridge
{

public:
	Bridge(sf::Vector2f startPos, sf::Vector2f endPos, int weight);
	virtual ~Bridge();

	//Accessor
	const sf::FloatRect GetBounds() const;

	void Update();
	void Render(sf::RenderTarget& target);

private:

	sf::RectangleShape brShape;
	int brWeight;
	sf::Text brText;
	sf::Font brFont;
	
};

#endif



