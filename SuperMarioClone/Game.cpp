#include <iostream>
#include <conio.h>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Coin.h"
#include "key.h"

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
}

Game::Game(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flag = 0;
	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!" << std::endl;

		window = SDL_CreateWindow(
			title,
			xPos,
			yPos,
			width,
			height,
			flag
		);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		else
		{
			std::cout << "Window initialisation failed: " << SDL_GetError() << std::endl;
			std::cout << "Prees any key to continue..." << std::endl;
			_getch();
			return;
		}

		renderer = SDL_CreateRenderer(
			window,
			-1,
			0
		);

		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;

			//Set display color
			int result = SDL_SetRenderDrawColor(
				renderer,
				255,
				255,
				255,
				255
			);
		}
		else
		{
			std::cout << "Window initialisation failed: " << SDL_GetError() << std::endl;
			std::cout << "Prees any key to continue..." << std::endl;
			_getch();
			return;
		}

		isRunning = true;


		Stats();

		ui.push_back(new UI("Assets/Font/Gameplay.ttf"));
		ui[0]->SetColor(255, 255, 255, 255);
		ui[0]->SetPos(0, 0, 200, 64);
		ui.push_back(new UI("Assets/Font/Gamer.ttf"));
		ui[1]->SetColor(255, 128, 0, 255);
		ui[1]->SetPos(width / 2 - 100, 0, 200, 80);
		ui.push_back(new UI("Assets/Font/Gameplay.ttf"));
		ui[2]->SetColor(255, 0, 0, 255);
		ui[2]->SetPos(width / 2 - 350, height / 2 - 90, 700, 90);
		ui.push_back(new UI("Assets/Font/Gameplay.ttf"));
		ui[3]->SetColor(0, 255, 0, 255);
		ui[3]->SetPos(width / 2 - 350, height / 2 - 90, 700, 90);

		map = new Map();
		map->LoadMap("Maps/Lv2.txt");

		input = new Input();

		player = new Player(input, map);

		camera = new Camera(player, map);

		key = new Key(camera, map, Vector2D(67 * 32, 29 * 32 + 1));

		enemies.push_back(new Enemy(camera, map, Vector2D(29 * 32, 31 * 32 + 1)));
		enemies.push_back(new Enemy(camera, map, Vector2D(8 * 32, 31 * 32 + 1)));
		enemies.push_back(new Enemy(camera, map, Vector2D(20 * 32, 31 * 32 + 1)));
		enemies.push_back(new Enemy(camera, map, Vector2D(25 * 32, 31 * 32 + 1)));

		flyEnemies.push_back(new Enemy2(camera, map, Vector2D(11 * 32, 25 * 32 + 1)));
		flyEnemies.push_back(new Enemy2(camera, map, Vector2D(40 * 32, 25 * 32 + 1)));

		coin.push_back(new Coin(camera, map, Vector2D(9 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(10 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(11 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(12 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(18 * 32, 24 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(24 * 32, 23 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(30 * 32, 21 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(44 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(45 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(46 * 32, 27 * 32 + 1)));
		coin.push_back(new Coin(camera, map, Vector2D(47 * 32, 27 * 32 + 1)));

		map->allocateCamera(camera);

		fadeTexture = EndGame();
	}
	else
	{
		isRunning = false;
	}
}

Game::~Game()
{
	clean();
}

void Game::HandleEvents()
{
	input->GetInput();

	if (input->KeyIsPressed(KEY_ESCAPE))
		isRunning = false;
}

void Game::Update()
{
	player->Update();
	camera->Update();

	for (int i = 0; i < coin.size(); i++)
	{
		coin[i]->Update();
	}
	key->Update();

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update();
	}
	for (int i = 0; i < flyEnemies.size(); i++)
	{
		flyEnemies[i]->AI(player->getPosition());
		flyEnemies[i]->Update();
	}


	for (int i = 0; i < enemies.size(); i++)
	{
		player->Collision(enemies[i]->getDestRect(), enemies[i]->getPosition());
		if(player->CanKIll())
			enemies[i]->Collision(player);
	}
	for (int i = 0; i < flyEnemies.size(); i++)
	{
		player->Collision(flyEnemies[i]->getDestRect(), flyEnemies[i]->getPosition());
		if (player->CanKIll())
			flyEnemies[i]->Collision(player);
	}

	for (int i = 0; i < coin.size(); i++)
	{
		if (coin[i]->Collision(player))
			coin.erase(coin.begin() + i);
	}

	//respawn enemies in case of death
	if (player->IsDead())
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Respawn();
		}
		for (int i = 0; i < flyEnemies.size(); i++)
		{
			flyEnemies[i]->Respawn();
		}
	}

	
	//score
	std::string result = "Score: " + std::to_string(Stats::getScore());
	ui[0]->Update(result);

	//lifes
	std::string result2 = "Lifes: " + std::to_string(Stats::getLifes());
	ui[1]->Update(result2);


	//lise and win text
	if (Stats::getLifes() <= 0)
	{
		std::string loseText = "You have lost! Press 'ESC' to Exit";

		ui[2]->Update(loseText);
	}
	else if (key->Collision(player))
	{
		std::string winText = "You have won! Press 'ESC' to Exit";

		ui[3]->Update(winText);

		Stats::winGame();
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);

	//add things to renderer
	map->DrawMap(true); 
	player->Render(camera->getDrawingRect()); 

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render();;
	}
	for (int i = 0; i < flyEnemies.size(); i++)
	{
		flyEnemies[i]->Render(player->getPosition());
	}
	for (int i = 0; i < coin.size(); i++)
	{
		coin[i]->Render();
	}
	key->Render();

	for (int i = 0; i < ui.size(); i++)
	{
		ui[i]->Render();
	}

	if (Stats::lifes <= 0)
	{
		EndGameRender();
		ui[2]->Render();
	}
	else if (Stats::getVictory())
	{
		EndGameRender();
		ui[3]->Render();
	}
	SDL_RenderPresent(renderer);
}

SDL_Texture* Game::EndGame()
{
	int screenW, screenH;
	SDL_GetRendererOutputSize(renderer, &screenW, &screenH);

	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, screenW, screenH, 32, 0, 0, 0, 0);
	
	Uint32 colour = SDL_MapRGBA(tempSurface->format, 0, 0, 0, 0);
	
	SDL_FillRect(tempSurface, NULL, colour);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	
	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;
	
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, 150);
	
	return texture;
}

void Game::EndGameRender()
{
	SDL_RenderCopy(renderer, fadeTexture, NULL, NULL);
}

void Game::clean()
{
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	if (enemies.size() > 0)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		enemies.clear();
	}
	if (flyEnemies.size() > 0)
	{
		for (int i = 0; i < flyEnemies.size(); i++)
		{
			delete flyEnemies[i];
			flyEnemies[i] = nullptr;
		}
		flyEnemies.clear();
	}
	if (coin.size() > 0)
	{
		for (int i = 0; i < coin.size(); i++)
		{
			delete coin[i];
			coin[i] = nullptr;
		}
		coin.clear();
	}
	if (ui.size() > 0)
	{
		for (int i = 0; i < ui.size(); i++)
		{
			delete ui[i];
			ui[i] = nullptr;
		}
		ui.clear();
	}
	if (input != nullptr)
	{
		delete input;
		input = nullptr;
	}
	if (map != nullptr)
	{
		delete map;
		map = nullptr;
	}

	if (renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}
	if (window != nullptr)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	SDL_Quit();

	std::cout << "Game Over" << std::endl;
}
