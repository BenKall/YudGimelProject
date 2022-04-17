#ifndef ANT_H
#define ANT_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include "AssetManager.h"
#include "UsefulFunctions.h"

class Ant
{

public:
	Ant(sf::Vector2f spawnPoint, sf::Vector2f despawnPoint,
		int spawnCoordinate, int despawnCoordinate,
		float movementSpeed, int antsContained,
		int screenWidth, int screenHeight);
	virtual ~Ant();

	//Accessor
	const sf::FloatRect GetBounds() const;
	const int GetSpawnCoordinate() const;
	const int GetDespawnCoordinate() const;
	const int GetAntAmount() const;

	bool IsAntDone();

	void Update();
	void Render(sf::RenderTarget* target);

private:

	sf::Sprite antSprite;
	sf::Vector2f direction;
	sf::Vector2f despawnPoint;
	float movementSpeed;
	int antAmount;
	sf::Text antText;
	sf::Font antFont;
	int spawnCoordinate;
	int despawnCoordinate;
};

#endif

