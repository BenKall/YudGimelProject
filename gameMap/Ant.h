#ifndef ANT_H
#define ANT_H

#include<SFML/Graphics.hpp>
#include<iostream>
#include "AssetManager.h"
#include "UsefulFunctions.h"
#include "Constants.h"

class Ant
{

public:
	Ant(sf::Vector2f spawnPoint, sf::Vector2f despawnPoint,
		int spawnCoordinate, int despawnCoordinate,
		float movementSpeed, int antsContained,
		ISLANDSTATUS status,
		int screenWidth, int screenHeight);
	/*virtual ~Ant();*/

	//Accessor
	const sf::FloatRect GetBounds() const;
	const int GetSpawnCoordinate() const;
	const int GetDespawnCoordinate() const;
	const int GetAntAmount() const;
	const ISLANDSTATUS GetStatus() const;

	bool IsAntDone();

	void Update();
	void Render(sf::RenderTarget* target);

private:

	sf::Sprite* antSprite = new sf::Sprite();
	sf::Vector2f* direction = new sf::Vector2f();
	sf::Vector2f* despawnPoint = new sf::Vector2f();
	float movementSpeed;
	int antAmount;
	sf::Text* antText = new sf::Text();
	sf::Font* antFont = new sf::Font();
	ISLANDSTATUS* status = new ISLANDSTATUS();
	int spawnCoordinate;
	int despawnCoordinate;
};

#endif

