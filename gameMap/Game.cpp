#include "Game.h"

Game::Game()
{
	initWindow();
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

void Game::run()
{
	while (this->window->isOpen())
	{
		this->UpdatePollEvents();
		this->Update();
		this->Render();
	}
}

void Game::UpdatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::UpdateInput()
{
	UpdateMouse();
}

void Game::UpdateMouse()
{
	mousePos = sf::Mouse::getPosition(*this->window);
	mousePosView = this->window->mapPixelToCoords(this->mousePos);
}

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
		if (this->curLevel.islands[i]->GetBounds().contains(this->mousePosView))
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
			delete this->ants.at(counter);
			this->ants.erase(this->ants.begin() + counter);
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

void Game::Update()
{
	UpdateInput();
	UpdateIslands();
	UpdateAnts();
}

void Game::Render()
{
	this->window->clear();
	if (flagShader)
	{
		backShader->setUniform("hasTexture", true);
		backShader->setUniform("texture", AssetManager::GetTexture("Assets/Textures/brazil.png"));
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
	this->window->display();
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(SCREENW, SCREENH), "Draw Circles", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(FRAMERATE);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initIsland()
{
	readLevel("level1.dat");

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
	//this->curLevel.bridgesCoordinates[0][1] = 6;
	//this->curLevel.bridgesCoordinates[0][2] = 6;
	//this->curLevel.bridgesCoordinates[1][3] = 3;
	//this->curLevel.bridgesCoordinates[2][3] = 3;
	//this->curLevel.bridgesCoordinates[3][4] = 3;
	//this->curLevel.bridgesCoordinates[3][5] = 3;
	//this->curLevel.bridgesCoordinates[4][6] = 6;
	//this->curLevel.bridgesCoordinates[5][6] = 6;




	/*writeLevel("level2.dat");
	readLevel("level2.dat");*/

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
	this->ai = new AiDijkstra(curLevel);
}

void Game::initShader()
{
	this->backShader = AssetManager::GetShader("vertex_shader.vert", "fragment_shader.frag");
	flagShader = 0;
}

void Game::initBackground()
{
	this->backgroundSprite = sf::Sprite(AssetManager::GetTexture("Assets/Textures/brazil.png"));
}
