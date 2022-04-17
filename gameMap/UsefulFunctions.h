#ifndef USEFULFUNCTIONS_H
#define USEFULFUNCTIONS_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <time.h>
#include <math.h>
class UsefulFunctions
{
public:
	//Calculation functions
	static float CalculateLength(sf::Vector2f ilPos1, sf::Vector2f ilPos2);
	static float CalculateAngle(sf::Vector2f ilPos1, sf::Vector2f ilPos2);
	static sf::Vector2f GetDirection(sf::Vector2f ilPos1, sf::Vector2f ilPos2);

};

#endif

