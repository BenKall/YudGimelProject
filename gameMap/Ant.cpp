#include "Ant.h"

Ant::Ant(sf::Vector2f spawnPoint, sf::Vector2f despawnPoint, int spawnCoordinate, int despawnCoordinate, float movementSpeed, int antsContained, ISLANDSTATUS status, int screenWidth, int screenHeight)
{
	//Sprite initiation
	this->antSprite.setTexture(AssetManager::GetTexture("Assets/Textures/ant1.png"));
	float antAngle = UsefulFunctions::CalculateAngle(spawnPoint, despawnPoint);
	this->antSprite.setPosition(spawnPoint);
	this->antSprite.setRotation(antAngle + 90);
	antSprite.setOrigin(
		antSprite.getGlobalBounds().width / 2,
		antSprite.getGlobalBounds().height / 2
	);

	this->antAmount = antsContained / 2;
	this->antAmount += antsContained % 2 ? 1 : 0;

	//Set text
	this->antFont = AssetManager::GetFont("Assets/Fonts/space age.ttf");

	//Set status
	this->status = status;

	this->antText.setFont(antFont);
	this->antText.setCharacterSize(24);
	this->antText.setFillColor(sf::Color::Black);
	this->antText.setOutlineColor(sf::Color::White);
	this->antText.setOutlineThickness(3.0f);
	std::string textString = std::to_string(antAmount);
	this->antText.setString(textString);
	sf::Vector2f brVector = UsefulFunctions::GetDirection(spawnPoint, despawnPoint);
	this->antText.setPosition(antSprite.getPosition().x, antSprite.getPosition().y);

	// Set other variables
	this->direction = UsefulFunctions::GetDirection(spawnPoint, despawnPoint);

	this->despawnPoint = despawnPoint;
	this->movementSpeed = movementSpeed;

	this->spawnCoordinate = spawnCoordinate;
	this->despawnCoordinate = despawnCoordinate;
}

Ant::~Ant()
{
}

const sf::FloatRect Ant::GetBounds() const
{
	return this->antSprite.getGlobalBounds();
}

const int Ant::GetSpawnCoordinate() const
{
	return this->spawnCoordinate;
}

const int Ant::GetDespawnCoordinate() const
{
	return this->despawnCoordinate;
}

const int Ant::GetAntAmount() const
{
	return this->antAmount;
}

const ISLANDSTATUS Ant::GetStatus() const
{
	return this->status;
}

bool Ant::IsAntDone()
{
	if (GetBounds().contains(this->despawnPoint))
	{
		return true;
	}
	return false;

	//my prior idea
	/*if (abs(this->antSprite.getPosition().x - this->despawnPoint.x) <
		this->movementSpeed &&
		abs(this->antSprite.getPosition().y - this->despawnPoint.y) <
		this->movementSpeed)
	{
		return true;
	}*/
}

void Ant::Update()
{
	this->antText.setPosition(antSprite.getPosition().x, antSprite.getPosition().y);
	this->antSprite.move(this->movementSpeed * this->direction);
}

void Ant::Render(sf::RenderTarget * target)
{
	target->draw(this->antSprite);
	target->draw(this->antText);
}
