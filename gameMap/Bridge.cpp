#include "Bridge.h"

Bridge::Bridge(sf::Vector2f startPos, sf::Vector2f endPos, int weight)
{
	float brLentgh = UsefulFunctions::CalculateLength(startPos, endPos);
	float brAngle = UsefulFunctions::CalculateAngle(startPos, endPos);
	
	// angle between 0-90
	float brQuarterAngle = static_cast<float>(static_cast<int>(abs(brAngle)) % 90);
	//Set shape
	sf::RectangleShape tmpRectangle;
	tmpRectangle.setFillColor(sf::Color::Black);
	tmpRectangle.setPosition(startPos);
	tmpRectangle.setSize(sf::Vector2f(brLentgh, 10.f));
	tmpRectangle.setRotation(brAngle);

	this->brShape = tmpRectangle;
	this->brWeight = weight;

	this->brFont = AssetManager::GetFont("Assets/Fonts/space age.ttf");

	//Set text
	this->brText.setFont(brFont);
	this->brText.setCharacterSize(24);
	this->brText.setFillColor(sf::Color::Black);
	this->brText.setOutlineColor(sf::Color::White);
	this->brText.setOutlineThickness(3.0f);
	std::string textString = std::to_string(this->brWeight);
	this->brText.setString(textString);
	sf::Vector2f brVector = UsefulFunctions::GetDirection(startPos, endPos);
	this->brText.setPosition(brShape.getPosition().x + brVector.x / 2, brShape.getPosition().y + brVector.y / 2);

	// move text next to bridge, by moving  it 
	// left or down, depending on the angle
	// so the text won't end up on the actual bridge
	if (brQuarterAngle > 45)
	{
		this->brText.move(10.f, 0);
	}
	else
	{
		this->brText.move(0, 20.f);
	}
	//this->brText.setPosition(brShape.getPosition().x + brShape.getGlobalBounds().width / 2, brShape.getPosition().y + brShape.getGlobalBounds().height / 2);
	//this->brText.setPosition(brShape.getPosition().x + abs(brVector.x) / 2, brShape.getPosition().y + abs(brVector.y) / 2);
	//this->brText.setPosition(tan(angle) / (180 / M_PI) * brShape.getPosition().x + brShape.getGlobalBounds().width / 2, tan(angle) / (180 / M_PI) * brShape.getPosition().y + brShape.getGlobalBounds().height / 2);


}

Bridge::~Bridge()
{
}

const sf::FloatRect Bridge::GetBounds() const
{
	return this->brShape.getGlobalBounds();
}

void Bridge::Render(sf::RenderTarget & target)
{
	target.draw(this->brShape);
	target.draw(this->brText);
}
