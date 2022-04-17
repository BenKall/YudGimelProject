#include "Game.h"

Game::Game()
{
	ilFirstClckd = -1;
	ilSecondClckd = -1;
	this->deltaTime = sf::milliseconds(1000);
	initWindow();
	initShader();
	initBackground();
	initIsland();
}

Game::~Game()
{
	delete this->window;

	for (int i = 0; i < ILNUMLEVEL1; i++)
	{
		delete islands[i];
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
	if (bridgesCoordinates[i][j])
		return true;
	return false;
}

void Game::CreateBridge(int i, int j, int weight)
{
	sf::Vector2f ilPos1 = sf::Vector2f(
		this->islands[i]->GetPos().x + this->islands[i]->GetBounds().width / 2,
		this->islands[i]->GetPos().y + this->islands[i]->GetBounds().height / 2);
	sf::Vector2f ilPos2 = sf::Vector2f(
		this->islands[j]->GetPos().x + this->islands[j]->GetBounds().width / 2,
		this->islands[j]->GetPos().y + this->islands[j]->GetBounds().height / 2);

	Bridge* tmpBridge = new Bridge(ilPos1, ilPos2, weight);

	this->bridges.push_back(tmpBridge);

}

void Game::CreateAnt(int i, int j, int weight)
{
	sf::Vector2f spawnPoint = sf::Vector2f(
		this->islands[i]->GetPos().x + this->islands[i]->GetBounds().width / 2,
		this->islands[i]->GetPos().y + this->islands[i]->GetBounds().height / 2);
	sf::Vector2f despawnPoint = sf::Vector2f(
		this->islands[j]->GetPos().x + this->islands[j]->GetBounds().width / 2,
		this->islands[j]->GetPos().y + this->islands[j]->GetBounds().height / 2);

	// movementSpeed = every second move ant (1 / weight) of your way,
	// so that it will take the ant (weight) seconds to reach the goal
	float movementSpeed = 1 / static_cast<float>(weight) / FRAMERATE;
	Ant* tmpAnt = new Ant(spawnPoint, despawnPoint, i, j, movementSpeed, this->islands[i]->GetAntsContained(), SCREENW, SCREENH);

	this->ants.push_back(tmpAnt);

	//Update island info
	islands[i]->DivideAntsContained();
}

//-----------------------------------------------------------------
//                      Calculate Length
//                      ----------------
// 
// Calculates the length between the previous position of the mouse
// and its current position.
//-----------------------------------------------------------------
float Game::CalculateLength(sf::Vector2f ilPos1, sf::Vector2f ilPos2)
{
	return sqrt((ilPos1.x - ilPos2.x) * (ilPos1.x - ilPos2.x) +
		(ilPos1.y - ilPos2.y) * (ilPos1.y - ilPos2.y));
}

//-----------------------------------------------------------------
//                        Calculate Angle
//                        ----------------
// 
// Calculates the angle between the previous position of the mouse
// and its current position.
// Doing so by calculating the inverse tangent of the adjacent and
// opposite sides of a triangle created with the two points.
// Then checks the direction of the drawn line in order to rotate
// the drawn rectangle correctly. 
//-----------------------------------------------------------------
float Game::CalculateAngle(sf::Vector2f ilPos1, sf::Vector2f ilPos2)
{

	float HorizontalDiff = ilPos1.x - ilPos2.x;
	float VerticalDiff = ilPos1.y - ilPos2.y;
	if (HorizontalDiff != 0)
	{
		double finalAngle = atan(abs(VerticalDiff) / abs(HorizontalDiff)) * (180 / M_PI);

		if (HorizontalDiff < 0 && VerticalDiff < 0 ||
			HorizontalDiff > 0 && VerticalDiff > 0) // From top left to bottom right or the opposite
			finalAngle += (HorizontalDiff > 0) ? -180 : 0;

		if (HorizontalDiff < 0 && VerticalDiff > 0) // From top right to bottom left
			finalAngle = -finalAngle ;
		if (HorizontalDiff > 0 && VerticalDiff < 0) // From bottom left to top right
			finalAngle = -finalAngle - 180;

		if (VerticalDiff == 0) // From left to right or the opposite
			finalAngle = (HorizontalDiff > 0) ? -180 : 0;

		return finalAngle;
	}
	return (VerticalDiff > 0) ? 0 : 180; // From top to bottom or the opposite

}

void Game::UpdateIslands()
{
	int flagIncreament = 0;
	elapsedTime += r.restart();
	if (this->elapsedTime >= this->deltaTime)
	{
		flagIncreament = 1;
		this->elapsedTime -= this->deltaTime;
	}
	this->flagShader = 0;
	for (int i = 0; i < ILNUMLEVEL1; i++)
	{
		//Increament ant amount
		if (this->islands[i]->GetStatus())
		{
			this->islands[i]->AddAntsContained(flagIncreament);
		}



		sf::Color curColor = this->islands[i]->GetOutlineColor();
		//if mouse is hovering over the shape
		if (this->islands[i]->GetBounds().contains(this->mousePosView))
		{
			this->flagShader = 1;
			backShader->setUniform("light", 
				sf::Vector2f(
					this->islands[i]->GetPos().x + this->islands[i]->GetBounds().width / 2,
					this->islands[i]->GetPos().y + this->islands[i]->GetBounds().height / 2)
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
						this->islands[i]->SetOutlineColor(PLAYERCOLOR);
					}
					else if (this->ilClicked[i] == 1)
					{
						this->ilClicked[i] = 0;
						this->islands[i]->SetOutlineColor(DEFAULTCOLOR);
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
							if (bridgesCoordinates[ilFirstClckd][ilSecondClckd])
							{
								CreateAnt(ilFirstClckd, ilSecondClckd, bridgesCoordinates[ilFirstClckd][ilSecondClckd]);
							}
							if (bridgesCoordinates[ilSecondClckd][ilFirstClckd])
							{
								CreateAnt(ilFirstClckd, ilSecondClckd, bridgesCoordinates[ilSecondClckd][ilFirstClckd]);
							}
							if (bridgesCoordinates[ilFirstClckd][ilSecondClckd] == 0 &&
								bridgesCoordinates[ilSecondClckd][ilFirstClckd] == 0)
							{
								this->ilClicked[ilFirstClckd] = 0;
								this->islands[ilFirstClckd]->SetOutlineColor(DEFAULTCOLOR);
								ilFirstClckd = i;
								ilSecondClckd = -1;
							}
						}
						if (ilSecondClckd != -1)
						{
							//Undo selection
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
}

void Game::UpdateAnts()
{
	unsigned counter = 0;
	for (auto *ant : this->ants)
	{
		ant->Update();

		if (ant->IsAntDone())
		{
			islands[ant->GetDespawnCoordinate()]->AddAntsContained(ant->GetAntAmount());
			//Delete ant
			delete this->ants.at(counter);
			this->ants.erase(this->ants.begin() + counter);
		}

		counter++;
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
	for (int i = 0; i < ILNUMLEVEL1; i++)
	{
		islands[i]->Render(*(this->window));
	}
	this->window->display();
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1080, 720), "Draw Circles", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(FRAMERATE);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initIsland()
{
	this->islands = new Island *[ILNUMLEVEL1];
	this->islands[0] = new Island(sf::Vector2f((float)(17 * SCREENW / 43), (float)(SCREENH / 14)), 1, CONTROLOFPLAYER);
	this->islands[1] = new Island(sf::Vector2f((float)(77 * SCREENW / 87), (float)(SCREENH / 16)), 2, NEUTRAL);
	this->islands[2] = new Island(sf::Vector2f((float)(SCREENW / 12), (float)(SCREENH / 3)), 3, NEUTRAL);
	this->islands[3] = new Island(sf::Vector2f((float)(SCREENW / 5), (float)(SCREENH / 6)), 4, NEUTRAL);
	this->islands[4] = new Island(sf::Vector2f((float)(4 * SCREENW / 7), (float)(3 * SCREENH / 8)), 5, NEUTRAL);
	this->islands[5] = new Island(sf::Vector2f((float)(4 * SCREENW / 5), (float)(SCREENH / 2)), 6, CONTROLOFENEMY);

	this->ilClicked = (int*)realloc(ilClicked, ILNUMLEVEL1 * sizeof(int)); //this better not cause any memory problems later on

	// Initialize lines matrix
	this->bridgesCoordinates = (int**)calloc(ILNUMLEVEL1 , sizeof(int*));
	for (size_t i = 0; i < ILNUMLEVEL1; i++)
	{
		this->bridgesCoordinates[i] = (int*)calloc(ILNUMLEVEL1, sizeof(int));
		ilClicked[i] = 0;
	}
	
	// Initialize line positions
	bridgesCoordinates[0][1] = 10;
	bridgesCoordinates[1][4] = 7;
	bridgesCoordinates[2][3] = 3;
	bridgesCoordinates[2][4] = 5;
	bridgesCoordinates[3][4] = 12;
	bridgesCoordinates[4][5] = 2;

	// Print matrix values
	/*for (int i = 0; i < ILNUMLEVEL1; i++)
	{
		for (int j = 0; j < ILNUMLEVEL1; j++)
		{
			printf("%d", ilLineCoordinates[i][j]);
		}
		printf("\n");
	}*/

	// Create bridges
	for (int i = 0; i < ILNUMLEVEL1; i++)
	{
		for (int j = i + 1; j < ILNUMLEVEL1; j++)
		{
			//BridgesCoordinates[i][j] = j + 1;
			if (bridgesCoordinates[i][j] > 0)
			{

				CreateBridge(i, j, bridgesCoordinates[i][j]);
			}
		}
	}
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
