#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "TextureManager.h"
#include "Stats.h"
#include "UI.h"
#include "Collision.h"
#include "GameObject.h"
#include "Map.h"
#include "Input.h"
#include "Camera.h"

class Player;
class Enemy;
class Enemy2;
class Coin;
class Map;
class Input;
class Camera;
class UI;
class Key;


class Game
{
private:
	SDL_Window* window{ nullptr };

	//Fading Screen
	SDL_Texture* fadeTexture{ nullptr };
	
	Player* player{ nullptr };
	Input* input{ nullptr };
	Map* map{ nullptr };
	Camera* camera{ nullptr };
	Key* key{ nullptr };

	bool isRunning = false;

	std::vector<Enemy*> enemies;
	std::vector<Enemy2*> flyEnemies;
	std::vector<Coin*> coin;
	std::vector<UI*> ui;

public:
	Game();
	Game(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	~Game();

	void HandleEvents();
	void Update();
	void Render();
	SDL_Texture* EndGame();
	void EndGameRender();
	void clean();
	bool running() { return isRunning; };

	static SDL_Renderer* renderer; //avoid allocating a pointer to it each time 
};

