#ifndef GAME_H
#define GAME_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <time.h>
#include <math.h>
#include "constants.h"
#include "Island.h"
#include "Ant.h"
#include "Bridge.h"

class Game
{
public:
	Game();
	virtual ~Game();


	//functions
	void run();

	//Calculation functions
	float CalculateLength(sf::Vector2f ilPos1, sf::Vector2f ilPos2);
	float CalculateAngle(sf::Vector2f ilPos1, sf::Vector2f ilPos2);
	//Check is line exists
	bool IsLineExist(int i, int j);

	//Update functions
	void UpdatePollEvents();
	void UpdateInput();
	//void updateKeyboardInput();
	void UpdateMouse();
	void updateMouseInteraction();
	void updateMousePositions();
	//void updateMousePosGrid();
	//void updateWorldCollision();
	void UpdateIslands();
	void UpdateAnts();
	
	//Create lines
	void CreateBridge(int i, int j, int weight);

	//Create Ants
	void CreateAnt(int i, int j, int weight);

	//
	void Update();
	void Render();

private:
	//Window
	sf::RenderWindow* window;

	//Shader
	sf::Shader* backShader; 
	int flagShader;

	//Time
	sf::Time elapsedTime;
	sf::Time deltaTime;
	sf::Clock r;

	//Island
	Island** islands;
	int* ilClicked = (int*)malloc(sizeof(int)); //watch out this won't become a memory problem

	//Islands clicked
	int ilFirstClckd;
	int ilSecondClckd;

	//Bridges locations
	int** bridgesCoordinates;
	
	//Bridges
	std::vector<Bridge*> bridges;

	//Ants
	std::vector<Ant*> ants;

	//MouseTracker
	sf::Vector2f mousePosGrid;

	//Mouse positions
	sf::Vector2i mousePos;
	sf::Vector2f mousePosView;
	bool mousePressed = false;

	//NextPos
	sf::FloatRect nextPos;

	//Background
	sf::Sprite backgroundSprite;

	//
	sf::Font font;
	sf::Text textTemplate;


	//private functions
	void initWindow();
	void initIsland();
	void initShader();
	void initBackground();
	//void initWall();


};

#endif


