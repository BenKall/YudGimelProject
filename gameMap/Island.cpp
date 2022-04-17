#include "Island.h"

void Island::InitIsland()
{
	this->ilShape.setRadius(80.f);
	this->ilShape.setOutlineColor(DEFAULTCOLOR);
	this->ilShape.setOutlineThickness(4.f);
	this->ilTexture = AssetManager::GetTexture("Assets/Textures/dirt_circle1.png");//.loadFromFile("Assets/Textures/dirt_circle1.png"); //
	this->ilShape.setTexture(&ilTexture);

	//Set text
	this->ilFont = AssetManager::GetFont("Assets/Fonts/space age.ttf");

	this->ilText.setFont(ilFont);
	this->ilText.setCharacterSize(74);
	this->ilText.setFillColor(sf::Color::Black);
	this->ilText.setOutlineColor(sf::Color::White);
	this->ilText.setOutlineThickness(3.0f);
}

Island::Island(sf::Vector2f pos, int antsContained, ISLANDSTATUS status)
{
	InitIsland();

	//Set status
	this->status = status;

	this->ilShape.setPosition(pos.x, pos.y);
	this->ilText.setPosition(pos.x + ilShape.getLocalBounds().width / 2, pos.y + ilShape.getLocalBounds().height / 2);
	this->ilText.setString(std::to_string(antsContained));
	this->ilText.setOrigin(ilText.getLocalBounds().width / 2, (ilText.getLocalBounds().height / 2) + ilText.getCharacterSize() / 2);
	// how many ants the island contains
	this->antsContained = antsContained;
}

const sf::FloatRect Island::GetBounds() const
{
	return this->ilShape.getGlobalBounds();

}

void Island::DivideAntsContained()
{
	this->antsContained /= 2;
	SetText(this->antsContained);
}

void Island::AddAntsContained(int amount)
{
	this->antsContained += amount;
	SetText(this->antsContained);
}

void Island::SetText(int newNumber)
{
	this->ilText.setString(std::to_string(newNumber));
	this->ilText.setOrigin(ilText.getLocalBounds().width / 2, (ilText.getLocalBounds().height / 2) + ilText.getCharacterSize() / 2);
}

void Island::SetOutlineColor(const sf::Color color)
{
	this->ilShape.setOutlineColor(color);
}

const sf::Vector2f & Island::GetPos() const
{
	return this->ilShape.getPosition();
}

const sf::Color Island::GetOutlineColor() const
{
	return this->ilShape.getOutlineColor();
}

const int Island::GetAntsContained() const
{
	return this->antsContained;
}

const ISLANDSTATUS Island::GetStatus() const
{
	return this->status;
}

void Island::Render(sf::RenderWindow & target)
{
	target.draw(this->ilShape);
	target.draw(this->ilText);
}
