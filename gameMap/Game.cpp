#include "Game.h"

Game::Game(sf::RenderWindow* window, SCREENTYPE& curScreen, int levelNum, int aiNum) : Screen(window, curScreen)
{
	this->backButton = new BtnOnlyText(0.05f, 0.06f, window->getSize().x, window->getSize().y, "Back", curScreen, GAMESELECT);
	initChosenLevelAndAi(levelNum, aiNum);
	initWindow(window);
	initShader();
	initBackground();
	initIsland();
	initAiEnemy();
}

Game::~Game()
{
	delete this->window;

	for (int i = 0; i < this->curLevel.size; i++)
	{
		delete this->curLevel.islands[i];
	}

	//Delete bridges
	for (auto *i : this->bridges)
	{
		delete i;
	}

	//Delete ants
	for (auto *i : this->ants)
	{
		delete i;
	}
}

//void Game::run()
//{
//	while (this->window->isOpen())
//	{
//		this->UpdatePollEvents();
//		this->Update();
//		this->Render();
//	}
//}

//void Game::UpdatePollEvents()
//{
//	sf::Event e;
//	while (this->window->pollEvent(e))
//	{
//		if (e.Event::type == sf::Event::Closed)
//		{
//			this->window->close();
//		}
//	}
//}

//void Game::UpdateInput()
//{
//	UpdateMouse();
//}

//void Game::UpdateMouse()
//{
//	mousePos = sf::Mouse::getPosition(*this->window);
//	mousePosView = this->window->mapPixelToCoords(this->mousePos);
//}

bool Game::IsLineExist(int i, int j)
{
	if (this->curLevel.bridgesCoordinates[i][j])
		return true;
	return false;
}

void Game::CreateBridge(int i, int j, int weight)
{
	sf::Vector2f ilPos1 = sf::Vector2f(
		this->curLevel.islands[i]->GetPos().x + this->curLevel.islands[i]->GetBounds().width / 2,
		this->curLevel.islands[i]->GetPos().y + this->curLevel.islands[i]->GetBounds().height / 2);
	sf::Vector2f ilPos2 = sf::Vector2f(
		this->curLevel.islands[j]->GetPos().x + this->curLevel.islands[j]->GetBounds().width / 2,
		this->curLevel.islands[j]->GetPos().y + this->curLevel.islands[j]->GetBounds().height / 2);

	Bridge* tmpBridge = new Bridge(ilPos1, ilPos2, weight, SCREENW, SCREENH);

	this->bridges.push_back(tmpBridge);

}

void Game::CreateAnt(int i, int j, int weight)
{
	if (this->curLevel.islands[i]->GetAntsContained() > 1)
	{
		sf::Vector2f spawnPoint = sf::Vector2f(
			this->curLevel.islands[i]->GetPos().x + this->curLevel.islands[i]->GetBounds().width / 2,
			this->curLevel.islands[i]->GetPos().y + this->curLevel.islands[i]->GetBounds().height / 2);
		sf::Vector2f despawnPoint = sf::Vector2f(
			this->curLevel.islands[j]->GetPos().x + this->curLevel.islands[j]->GetBounds().width / 2,
			this->curLevel.islands[j]->GetPos().y + this->curLevel.islands[j]->GetBounds().height / 2);

		// movementSpeed = every second move ant (1 / weight) of your way,
		// so that it will take the ant (weight) seconds to reach the goal
		float movementSpeed = 1 / static_cast<float>(weight) / FRAMERATE;
		Ant* tmpAnt = new Ant(
			spawnPoint, despawnPoint,
			i, j, movementSpeed,
			this->curLevel.islands[i]->GetAntsContained(),
			this->curLevel.islands[i]->GetStatus(),
			SCREENW, SCREENH);

		this->ants.push_back(tmpAnt);

		//Update island info
		this->curLevel.islands[i]->DivideAntsContained();
	}
}
	

void Game::UpdateIslands()
{
	int flagIncreament = 0;
	elapsedTime += clock.restart();
	if (this->elapsedTime >= this->deltaTime)
	{
		flagIncreament = 1;
		this->elapsedTime -= this->deltaTime;
	}
	this->flagShader = 0;
	for (int i = 0; i < this->curLevel.size; i++)
	{
		//Increament ant amount
		if (this->curLevel.islands[i]->GetStatus())
		{
			this->curLevel.islands[i]->ChangeAntsContained(flagIncreament, this->curLevel.islands[i]->GetStatus());
		}



		sf::Color curColor = this->curLevel.islands[i]->GetOutlineColor();
		//if mouse is hovering over the shape
		if (this->curLevel.islands[i]->GetBounds().contains(*this->mousePosView))
		{
			this->flagShader = 1;
			backShader->setUniform("light", 
				sf::Vector2f(
					this->curLevel.islands[i]->GetPos().x + this->curLevel.islands[i]->GetBounds().width / 2,
					this->curLevel.islands[i]->GetPos().y + this->curLevel.islands[i]->GetBounds().height / 2)
			); 
			//if mouse is pressed
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				if (this->mousePressed == false)
				{
					//Change color
					this->mousePressed = true;
					if (this->ilClicked[i] == 0)
					{
						this->ilClicked[i] = 1;
						this->curLevel.islands[i]->SetOutlineColor(TXTPLAYERCOLOR);
					}
					else if (this->ilClicked[i] == 1)
					{
						this->ilClicked[i] = 0;
						this->curLevel.islands[i]->SetStatusColors(this->curLevel.islands[i]->GetStatus());
					}

					//Set selection

					//First selection
					if (this->ilFirstClckd == -1)
					{
						ilFirstClckd = i;
					}
					else
					{
						//Check if you didn't click on the same island 
						//for the second selection
						if (this->ilFirstClckd != i)
						{
							//Second selection
							ilSecondClckd = i;
							//Check if there is bridge connecting the islands
							if (this->curLevel.bridgesCoordinates[ilFirstClckd][ilSecondClckd])
							{
								CreateAnt(ilFirstClckd, ilSecondClckd, this->curLevel.bridgesCoordinates[ilFirstClckd][ilSecondClckd]);
							}
							if (this->curLevel.bridgesCoordinates[ilSecondClckd][ilFirstClckd])
							{
								CreateAnt(ilFirstClckd, ilSecondClckd, this->curLevel.bridgesCoordinates[ilSecondClckd][ilFirstClckd]);
							}
							if (this->curLevel.bridgesCoordinates[ilFirstClckd][ilSecondClckd] == 0 &&
								this->curLevel.bridgesCoordinates[ilSecondClckd][ilFirstClckd] == 0)
							{
								this->ilClicked[ilFirstClckd] = 0;
								this->curLevel.islands[ilFirstClckd]->SetStatusColors(this->curLevel.islands[ilFirstClckd]->GetStatus());
								ilFirstClckd = i;
								ilSecondClckd = -1;
							}
						}
						if (ilSecondClckd != -1)
						{
							//Undo selection
							this->curLevel.islands[ilFirstClckd]->SetStatusColors(this->curLevel.islands[ilFirstClckd]->GetStatus());
							this->curLevel.islands[ilSecondClckd]->SetStatusColors(this->curLevel.islands[ilSecondClckd]->GetStatus());
							this->ilClicked[ilFirstClckd] = 0;
							this->ilClicked[ilSecondClckd] = 0;
							ilFirstClckd = -1;
							ilSecondClckd = -1;
						}
						
						
					}

				}
			}
			else
			{
				this->mousePressed = false;
				//curColor = PLAYERCOLOR;
				//this->islands[i]->setOutlineColor(curColor);
			}
		}
		else
		{
			/*if (this->ilClicked[i] == 0)
			{
				this->islands[i]->setOutlineColor(DEFAULTCOLOR);
			}*/
		}
	}

	//Ai
	std::vector<AntBuildParameters> aiDecision = ai->Think(curLevel);

	for (auto i : aiDecision)
	{
		CreateAnt(i.startCoordinate, i.endCoordinate, i.weight);
	}
}

void Game::UpdateAnts()
{
	unsigned counter = 0;
	for (auto *ant : this->ants)
	{
		ant->Update();

		if (ant->IsAntDone())
		{
			this->curLevel.islands[ant->GetDespawnCoordinate()]->ChangeAntsContained(ant->GetAntAmount(), ant->GetStatus());
			//Delete ant
			//delete this->ants.at(counter);
			this->ants.erase(this->ants.begin() + counter);
			counter--;
		}

		counter++;
	}
}

void Game::writeLevel(std::string fileName)
{
	std::ofstream levelFile(fileName, std::ios::out | std::ios::binary);
	if (!levelFile) {
		std::cout << "Cannot open file!" << std::endl;
	}
	if (levelFile.is_open())
	{
		levelFile.write((char *)&this->curLevel.size, sizeof(int));
		for (int i = 0; i < this->curLevel.size; i++)
		{
			levelFile.write((char *)&this->curLevel.islands[i]->GetPos(), sizeof(sf::Vector2f));
			levelFile.write((char *)&this->curLevel.islands[i]->GetAntsContained(), sizeof(int));
			levelFile.write((char *)&this->curLevel.islands[i]->GetStatus(), sizeof(ISLANDSTATUS));
		}

		for (int i = 0; i < this->curLevel.size; i++)
		{
			for (int j = 0; j < this->curLevel.size; j++)
			{
				levelFile.write((char *)&this->curLevel.bridgesCoordinates[i][j], sizeof(int));
			}
		}
		levelFile.close();
	}
	if (!levelFile.good()) {
		std::cout << "Error occurred at writing time!" << std::endl;
	}

}

void Game::readLevel(std::string fileName)
{
	std::ifstream levelFileRead(fileName, std::ios::in | std::ios::binary);
	if (!levelFileRead) {
		std::cout << "Cannot open file!" << std::endl;
	}
	if (levelFileRead.is_open())
	{
		levelFileRead.read((char *)&this->curLevel.size, sizeof(int));
		this->curLevel.islands = new Island *[this->curLevel.size];
		for (int i = 0; i < this->curLevel.size; i++)
		{
			sf::Vector2f tmpVc2f;
			int tmpN;
			ISLANDSTATUS tmpIls;
			levelFileRead.read((char *)&tmpVc2f, sizeof(sf::Vector2f));
			levelFileRead.read((char *)&tmpN, sizeof(int));
			levelFileRead.read((char *)&tmpIls, sizeof(ISLANDSTATUS));
			this->curLevel.islands[i] = new Island(tmpVc2f, tmpN, tmpIls);
		}

		this->curLevel.bridgesCoordinates = (int**)calloc(this->curLevel.size, sizeof(int*));
		for (int i = 0; i < this->curLevel.size; i++)
		{
			this->curLevel.bridgesCoordinates[i] = (int*)calloc(this->curLevel.size, sizeof(int));
		}

		for (int i = 0; i < this->curLevel.size; i++)
		{
			for (int j = 0; j < this->curLevel.size; j++)
			{
				levelFileRead.read((char *)&this->curLevel.bridgesCoordinates[i][j], sizeof(int));
			}
		}
		levelFileRead.close();
	}
	if (!levelFileRead.good()) {
		std::cout << "Error occurred at writing time!" << std::endl;
	}
}

void Game::UpdateElements()
{
	this->backButton->CheckMouse(this->mousePosView);
	UpdateIslands();
	UpdateAnts();
}

void Game::Render()
{
	this->window->clear();
	if (flagShader)
	{
		backShader->setUniform("hasTexture", true);
		backShader->setUniform("texture", AssetManager::GetTexture("Assets/Textures/antgameBackground.png"));
		this->window->draw(backgroundSprite, backShader);
	}
	else
	{
		this->window->draw(backgroundSprite);
	}
	for (auto *bridge : this->bridges)
	{
		bridge->Render(*(this->window));
	}
	for (auto *ant : this->ants)
	{
		ant->Render(this->window);
	}
	for (int i = 0; i < this->curLevel.size; i++)
	{
		this->curLevel.islands[i]->Render(*(this->window));
	}
	this->backButton->Render(*(this->window));
	this->window->display();
}

void Game::initChosenLevelAndAi(int levelNum, int aiNum)
{
	this->levelString = "level1.dat";
	switch (levelNum)
	{
	case 1:
		this->levelString = "level1.dat";
		break;
	case 2:
		this->levelString = "level2.dat";
		break;
	case 3:
		this->levelString = "level3.dat"; 
		break;
	case 4:
		this->levelString = "level4.dat";
		break;
	default:
		break;
	}

	readLevel(this->levelString);

	this->ai = new AiAgressive(curLevel);
	switch (aiNum)
	{
	case 1:
		this->ai = new AiAgressive(curLevel);
		break;
	case 2:
		this->ai = new AiDijkstra(curLevel);
		break;
	default:
		break;
	}
}

void Game::initWindow(sf::RenderWindow* window)
{
	this->window = window;
	this->window->setFramerateLimit(FRAMERATE);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initIsland()
{
	//readLevel("level3.dat");

	/*this->curLevel.size = 19;
	this->curLevel.islands = new Island *[this->curLevel.size];
	this->curLevel.islands[0] = new Island(sf::Vector2f(0.05f, 0.1f), 0, CONTROLOFPLAYER);
	this->curLevel.islands[1] = new Island(sf::Vector2f(0.07f, 0.7f), 1, NEUTRAL);
	this->curLevel.islands[2] = new Island(sf::Vector2f(0.29f, 0.8f), 2, NEUTRAL);
	this->curLevel.islands[3] = new Island(sf::Vector2f(0.18f, 0.2f), 3, NEUTRAL);
	this->curLevel.islands[4] = new Island(sf::Vector2f(0.3f, 0.08f), 4, NEUTRAL);
	this->curLevel.islands[5] = new Island(sf::Vector2f(0.45f, 0.05f), 5, NEUTRAL);
	this->curLevel.islands[6] = new Island(sf::Vector2f(0.49f, 0.25f), 6, NEUTRAL);
	this->curLevel.islands[7] = new Island(sf::Vector2f(0.4f, 0.45f), 7, NEUTRAL);
	this->curLevel.islands[8] = new Island(sf::Vector2f(0.5f, 0.78f), 8, NEUTRAL);
	this->curLevel.islands[9] = new Island(sf::Vector2f(0.55f, 0.4f), 9, NEUTRAL);
	this->curLevel.islands[10] = new Island(sf::Vector2f(0.65f, 0.55f), 10, NEUTRAL);
	this->curLevel.islands[11] = new Island(sf::Vector2f(0.62f, 0.83f), 11, NEUTRAL);
	this->curLevel.islands[12] = new Island(sf::Vector2f(0.6f, 0.15f), 12, NEUTRAL);
	this->curLevel.islands[13] = new Island(sf::Vector2f(0.77f, 0.48f), 13, NEUTRAL);
	this->curLevel.islands[14] = new Island(sf::Vector2f(0.795f, 0.7f), 14, NEUTRAL);
	this->curLevel.islands[15] = new Island(sf::Vector2f(0.8f, 0.84f), 15, NEUTRAL);
	this->curLevel.islands[16] = new Island(sf::Vector2f(0.89f, 0.565f), 16, NEUTRAL);
	this->curLevel.islands[17] = new Island(sf::Vector2f(0.9f, 0.12f), 17, NEUTRAL);
	this->curLevel.islands[18] = new Island(sf::Vector2f(0.76f, 0.05f), 18, CONTROLOFENEMY);*/

	//this->curLevel.size = 7;
	//this->curLevel.islands = new Island *[this->curLevel.size];
	//this->curLevel.islands[0] = new Island(sf::Vector2f(0.05f, 0.3f), 20, CONTROLOFPLAYER);
	//this->curLevel.islands[1] = new Island(sf::Vector2f(0.25f, 0.1f), 0, NEUTRAL);
	//this->curLevel.islands[2] = new Island(sf::Vector2f(0.25f, 0.5f), 0, NEUTRAL);
	//this->curLevel.islands[3] = new Island(sf::Vector2f(0.45f, 0.3f), 30, NEUTRAL);
	//this->curLevel.islands[4] = new Island(sf::Vector2f(0.65f, 0.1f), 0, NEUTRAL);
	//this->curLevel.islands[5] = new Island(sf::Vector2f(0.65f, 0.5f), 0, NEUTRAL);
	//this->curLevel.islands[6] = new Island(sf::Vector2f(0.85f, 0.3f), 20, CONTROLOFENEMY);

	this->ilClicked = (int*)realloc(ilClicked, this->curLevel.size * sizeof(int)); //this better not cause any memory problems later on


	// //Initialize lines matrix
	//this->curLevel.bridgesCoordinates = (int**)calloc(this->curLevel.size , sizeof(int*));
	//for (int i = 0; i < this->curLevel.size; i++)
	//{
	//	this->curLevel.bridgesCoordinates[i] = (int*)calloc(this->curLevel.size, sizeof(int));
	//	ilClicked[i] = 0;
	//}
	//
	// //Initialize line positions
	//this->curLevel.bridgesCoordinates[0][3] = 1;
	//this->curLevel.bridgesCoordinates[0][4] = 5;
	//this->curLevel.bridgesCoordinates[1][2] = 2;
	//this->curLevel.bridgesCoordinates[2][4] = 7;
	//this->curLevel.bridgesCoordinates[2][8] = 2;
	//this->curLevel.bridgesCoordinates[3][4] = 2;
	//this->curLevel.bridgesCoordinates[4][5] = 3;
	//this->curLevel.bridgesCoordinates[5][6] = 3;
	//this->curLevel.bridgesCoordinates[6][7] = 2;
	//this->curLevel.bridgesCoordinates[6][9] = 1;
	//this->curLevel.bridgesCoordinates[6][12] = 5;
	//this->curLevel.bridgesCoordinates[7][10] = 2;
	//this->curLevel.bridgesCoordinates[8][11] = 1;
	//this->curLevel.bridgesCoordinates[9][10] = 4;
	//this->curLevel.bridgesCoordinates[10][12] = 6;
	//this->curLevel.bridgesCoordinates[10][13] = 1;
	//this->curLevel.bridgesCoordinates[11][13] = 6;
	//this->curLevel.bridgesCoordinates[11][15] = 4;
	//this->curLevel.bridgesCoordinates[12][17] = 3;
	//this->curLevel.bridgesCoordinates[12][18] = 2;
	//this->curLevel.bridgesCoordinates[13][14] = 2;
	//this->curLevel.bridgesCoordinates[13][16] = 3;
	//this->curLevel.bridgesCoordinates[15][16] = 2;
	

	// //Initialize lines matrix
	//this->curLevel.bridgesCoordinates = (int**)calloc(this->curLevel.size , sizeof(int*));
	//for (int i = 0; i < this->curLevel.size; i++)
	//{
	//	this->curLevel.bridgesCoordinates[i] = (int*)calloc(this->curLevel.size, sizeof(int));
	//	ilClicked[i] = 0;
	//}
	//
	// //Initialize line positions
	//this->curLevel.bridgesCoordinates[0][1] = 6;
	//this->curLevel.bridgesCoordinates[0][2] = 6;
	//this->curLevel.bridgesCoordinates[1][3] = 3;
	//this->curLevel.bridgesCoordinates[2][3] = 3;
	//this->curLevel.bridgesCoordinates[3][4] = 3;
	//this->curLevel.bridgesCoordinates[3][5] = 3;
	//this->curLevel.bridgesCoordinates[4][6] = 6;
	//this->curLevel.bridgesCoordinates[5][6] = 6;




	/*writeLevel("level4.dat");
	readLevel("level4.dat");*/

	// Print matrix values
	/*for (int i = 0; i < ILNUMLEVEL1; i++)
	{
		for (int j = 0; j < ILNUMLEVEL1; j++)
		{
			printf("%d", ilLineCoordinates[i][j]);
		}
		printf("\n");
	}*/

	//Set positions to screen size
	for (int i = 0; i < this->curLevel.size; i++)
	{
		this->curLevel.islands[i]->SetPosRelativeToScreen(SCREENW, SCREENH);
	}

	// Create bridges
	for (int i = 0; i < this->curLevel.size; i++)
	{
		for (int j = i + 1; j < this->curLevel.size; j++)
		{
			//BridgesCoordinates[i][j] = j + 1;
			if (this->curLevel.bridgesCoordinates[i][j] > 0)
			{

				CreateBridge(i, j, this->curLevel.bridgesCoordinates[i][j]);
			}
		}
	}


}

void Game::initAiEnemy()
{
	//this->ai = new AiAgressive(curLevel);
	//this->ai = new AiDijkstra(curLevel);
}

void Game::initShader()
{
	this->backShader = AssetManager::GetShader("vertex_shader.vert", "fragment_shader.frag");
	flagShader = 0;
}

void Game::initBackground()
{
	this->backgroundSprite = sf::Sprite(AssetManager::GetTexture("Assets/Textures/antgameBackground.png"));
	this->backgroundSprite.setScale(
		window->getSize().x / this->backgroundSprite.getGlobalBounds().width,
		window->getSize().y / this->backgroundSprite.getGlobalBounds().height
	);
}
