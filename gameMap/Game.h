#ifndef GAME_H
#define GAME_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <time.h>
#include <math.h>
#include <vector> //remove?
#include "Screen.h"
#include "constants.h"
#include "Island.h"
#include "Ant.h"
#include "Bridge.h"
#include "CustomStructs.h"
#include "AiEnemy.h"
#include "AiDijkstra.h"
#include "AiAgressive.h"
#include "BtnOnlyText.h"

class Game :
	public Screen
{
public:
	Game(sf::RenderWindow* window, SCREENTYPE& curScreen, int levelNum , int aiNum);
	virtual ~Game();

	//functions
	//void run();

	//Check is line exists
	bool IsLineExist(int i, int j);

	//Update functions
	//void UpdatePollEvents();
	//void UpdateInput();
	//void updateKeyboardInput();
	//void UpdateMouse();
	void updateMouseInteraction();
	void updateMousePositions();
	//void updateMousePosGrid();
	//void updateWorldCollision();
	void UpdateIslands();
	void UpdateAnts();
	
	//File functions
	void writeLevel(std::string fileName);
	void readLevel(std::string fileName);

	//Create lines
	void CreateBridge(int i, int j, int weight);

	//Create Ants
	void CreateAnt(int i, int j, int weight);

	//
	void UpdateElements();
	void Render();

private:
	//Window
	//sf::RenderWindow* window;

	//Shader
	sf::Shader* backShader; 
	int flagShader;

	//Time
	sf::Time elapsedTime;
	sf::Time deltaTime = sf::milliseconds(500);
	sf::Clock clock;

	//Island interface
	int* ilClicked; // = (int*)malloc(sizeof(int)); //watch out this won't become a memory problem

	//Islands clicked
	int ilFirstClckd = -1;
	int ilSecondClckd = -1;
	
	//Level
	Level curLevel;

	//Bridges
	std::vector<Bridge*> bridges;

	//Ants
	std::vector<Ant*> ants;

	//MouseTracker
	//sf::Vector2f mousePosGrid;

	//Mouse positions
	//sf::Vector2i mousePos;
	//sf::Vector2f mousePosView;
	bool mousePressed = false;

	//NextPos
	sf::FloatRect nextPos;

	//Background
	sf::Sprite backgroundSprite;

	//
	sf::Font font;
	sf::Text textTemplate;

	//Ai
	AiEnemy *ai;

	//Level
	sf::String levelString;

	//Back button
	BtnOnlyText* backButton;

	//private functions
	void initChosenLevelAndAi(int levelNum, int aiNum);
	void initWindow(sf::RenderWindow* window);
	void initIsland();
	void initAiEnemy();
	void initShader();
	void initBackground();
	//void initWall();


};

#endif


