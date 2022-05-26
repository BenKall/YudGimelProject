#include "Island.h"

Island::Island(sf::Vector2f pos, int antsContained, ISLANDSTATUS status)
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
	this->ilText.setOutlineColor(DEFAULTCOLOR);
	this->ilText.setOutlineThickness(3.f);
	//Set status
	this->status = status;

	//Set outlines
	SetStatusColors(status);

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

// add or sub amount of ants depending on ant type inside and incoming
void Island::ChangeAntsContained(int amount, ISLANDSTATUS status)
{
	if (this->status == status)
	{
		this->antsContained += amount;
	}
	else
	{
		int newAmount = this->antsContained - amount;
		if (newAmount < 0)
		{
			this->status = status;
			SetStatusColors(status);
		}
		if (newAmount == 0)
		{
			this->status = NEUTRAL;
			SetStatusColors(NEUTRAL);
		}
		this->antsContained = abs(newAmount);
	}
	SetText(this->antsContained);
}

void Island::SetText(int newNumber)
{
	this->ilText.setString(std::to_string(newNumber));
	this->ilText.setOrigin(ilText.getLocalBounds().width / 2, (ilText.getLocalBounds().height / 2) + ilText.getCharacterSize() / 2);
}

//Set the position and size of the island to the size of the screen
void Island::SetPosRelativeToScreen(int screenWidth, int screenHeight)
{
	this->ilShape.setRadius((screenWidth + screenHeight) / 2 / 20);
	this->ilShape.setOutlineThickness(this->ilShape.getRadius() / 16);
	this->ilShape.setPosition(
		this->ilShape.getPosition().x * screenWidth,
		this->ilShape.getPosition().y * screenHeight
	);
	/*this->ilShape.setOrigin(ilShape.getGlobalBounds().width / 2,
		ilShape.getGlobalBounds().height / 2)*/
	this->ilText.setCharacterSize(this->ilShape.getRadius());
	this->ilText.setOutlineThickness(this->ilText.getCharacterSize() / 16);

	this->ilText.setPosition(
		this->ilShape.getPosition().x + ilShape.getLocalBounds().width / 2,
		this->ilShape.getPosition().y + ilShape.getLocalBounds().height / 2
	);
	this->ilText.setOrigin(ilText.getLocalBounds().width / 2, (ilText.getLocalBounds().height / 2) + ilText.getCharacterSize() / 2);

}

void Island::SetOutlineColor(const sf::Color color)
{
	this->ilShape.setOutlineColor(color);
}

//Set the color of the island according to their status
void Island::SetStatusColors(ISLANDSTATUS status)
{
	//Set shape outline
	this->ilShape.setOutlineColor(DEFAULTCOLOR);
	if (status == CONTROLOFPLAYER)
	{
		this->ilShape.setOutlineColor(PLAYERCOLOR);
	}
	if (status == CONTROLOFENEMY)
	{
		this->ilShape.setOutlineColor(ENEMYCOLOR);
	}

	//Set text outline
	this->ilText.setOutlineColor(DEFAULTCOLOR);
	if (status == CONTROLOFPLAYER)
	{
		this->ilText.setOutlineColor(TXTPLAYERCOLOR);
	}
	if (status == CONTROLOFENEMY)
	{
		this->ilText.setOutlineColor(TXTENEMYCOLOR);
	}
}

const sf::Vector2f & Island::GetPos() const
{
	return this->ilShape.getPosition();
}

const sf::Color Island::GetOutlineColor() const
{
	return this->ilShape.getOutlineColor();
}

const int& Island::GetAntsContained() const
{
	return this->antsContained;
}

const ISLANDSTATUS& Island::GetStatus() const
{
	return this->status;
}

void Island::Render(sf::RenderWindow & target)
{
	target.draw(this->ilShape);
	target.draw(this->ilText);
}
