#include "Ant.h"

Ant::Ant(sf::Vector2f spawnPoint, sf::Vector2f despawnPoint, int spawnCoordinate, int despawnCoordinate, float movementSpeed, int antsContained, ISLANDSTATUS status, int screenWidth, int screenHeight)
{
	//Sprite initiation
	this->antSprite->setTexture(AssetManager::GetTexture("Assets/Textures/ant1.png"));
	this->antSprite->setScale((screenWidth + screenHeight) / 1000, (screenWidth + screenHeight) / 1000);
	float antAngle = UsefulFunctions::CalculateAngle(spawnPoint, despawnPoint);
	this->antSprite->setPosition(spawnPoint);
	this->antSprite->setRotation(antAngle + 90);
	antSprite->setOrigin(
		antSprite->getGlobalBounds().width / 2,
		antSprite->getGlobalBounds().height / 2
	);

	this->antAmount = antsContained / 2;
	this->antAmount += antsContained % 2 ? 1 : 0;

	//Set text
	*this->antFont = AssetManager::GetFont("Assets/Fonts/space age.ttf");

	//Set status
	*this->status = status;

	if (*this->status == CONTROLOFPLAYER)
		this->antSprite->setColor(sf::Color(60.f,255.f, 255.f));
	else
		this->antSprite->setColor(sf::Color(255.f, 60.f, 60.f));

	this->antText->setFont(*antFont);
	this->antText->setCharacterSize(24);
	this->antText->setFillColor(sf::Color::Black);
	this->antText->setOutlineColor(sf::Color::White);
	this->antText->setOutlineThickness(3.0f);
	std::string textString = std::to_string(antAmount);
	this->antText->setString(textString);
	sf::Vector2f brVector = UsefulFunctions::GetDirection(spawnPoint, despawnPoint);
	this->antText->setPosition(this->antSprite->getPosition().x, this->antSprite->getPosition().y);
	this->antText->setPosition(
		this->antSprite->getPosition().x + this->antSprite->getLocalBounds().width / 2,
		this->antSprite->getPosition().y + this->antSprite->getLocalBounds().height / 2
	);
	this->antText->setOrigin(this->antText->getLocalBounds().width / 2, (this->antText->getLocalBounds().height / 2) + this->antText->getCharacterSize() / 4);


	// Set other variables
	*this->direction = UsefulFunctions::GetDirection(spawnPoint, despawnPoint);

	*this->despawnPoint = despawnPoint;
	this->movementSpeed = movementSpeed;

	this->spawnCoordinate = spawnCoordinate;
	this->despawnCoordinate = despawnCoordinate;
}
//
//Ant::~Ant()
//{
//	delete this->antSprite;
//	delete this->direction;
//	delete this->despawnPoint;
//	//delete this->movementSpeed;
//	//delete this->antAmount;
//	delete this->antText;
//	delete this->antFont;
//	delete this->status;
//	//delete this->spawnCoordinate;
//	//delete this->despawnCoordinate;
//}

const sf::FloatRect Ant::GetBounds() const
{
	return this->antSprite->getGlobalBounds();
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
	return *this->status;
}

bool Ant::IsAntDone()
{
	if (GetBounds().contains(*this->despawnPoint))
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
	this->antText->setPosition(antSprite->getPosition().x, antSprite->getPosition().y);
	this->antSprite->move(this->movementSpeed * *this->direction);
}

void Ant::Render(sf::RenderTarget * target)
{
	target->draw(*this->antSprite);
	target->draw(*this->antText);
}
