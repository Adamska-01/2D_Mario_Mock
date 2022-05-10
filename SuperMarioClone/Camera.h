#pragma once
#include <SDL.h>
#include "Game.h"

class Player;
class Map;

class Camera
{
private:
	SDL_Rect cameraRect = SDL_Rect();

	Player* player = nullptr;
	Map* map = nullptr;

	int screenW{ 0 }, screenH{ 0 };

public:
	Camera();
	Camera(Player* m_player, Map* m_map);
	~Camera();

	void Update();
	SDL_Rect getDrawingRect();
	SDL_Rect getRect();
};