#include "UsefulFunctions.h"

// Calculates the length between 2 points
float UsefulFunctions::CalculateLength(sf::Vector2f ilPos1, sf::Vector2f ilPos2)
{
	return sqrt((ilPos1.x - ilPos2.x) * (ilPos1.x - ilPos2.x) +
		(ilPos1.y - ilPos2.y) * (ilPos1.y - ilPos2.y));
}

// Calculates the angle between 2 poits 
float UsefulFunctions::CalculateAngle(sf::Vector2f ilPos1, sf::Vector2f ilPos2)
{

	float HorizontalDiff = ilPos1.x - ilPos2.x;
	float VerticalDiff = ilPos1.y - ilPos2.y;
	if (HorizontalDiff != 0)
	{
		double finalAngle = atan(abs(VerticalDiff) / abs(HorizontalDiff)) * (180 / M_PI);

		if (HorizontalDiff < 0 && VerticalDiff < 0 ||
			HorizontalDiff > 0 && VerticalDiff > 0) // From top left to bottom right or the opposite
			finalAngle += (HorizontalDiff > 0) ? -180 : 0;

		if (HorizontalDiff < 0 && VerticalDiff > 0) // From top right to bottom left
			finalAngle = -finalAngle;
		if (HorizontalDiff > 0 && VerticalDiff < 0) // From bottom left to top right
			finalAngle = -finalAngle - 180;

		if (VerticalDiff == 0) // From left to right or the opposite
			finalAngle = (HorizontalDiff > 0) ? -180 : 0;

		return finalAngle;
	}
	return (VerticalDiff > 0) ? 0 : 180; // From top to bottom or the opposite

}

sf::Vector2f UsefulFunctions::GetDirection(sf::Vector2f ilPos1, sf::Vector2f ilPos2)
{
	return sf::Vector2f(ilPos2.x - ilPos1.x, ilPos2.y - ilPos1.y);
}
