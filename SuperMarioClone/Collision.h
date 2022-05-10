#pragma once
#include "Game.h"

class Collision
{
public:
	static bool CheckCollisionEntity(SDL_Rect rect1, SDL_Rect rect2); //not working with scrolling 
	static bool CheckCollisionEntity(SDL_Rect rect1, int x1, int y1, SDL_Rect rect2, int x2, int y2);
};