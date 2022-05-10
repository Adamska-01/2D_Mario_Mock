#include "Collision.h"

bool Collision::CheckCollisionEntity(SDL_Rect rect1, SDL_Rect rect2)
{
	if (
		rect1.x + rect1.w >= rect2.x &&
		rect2.x + rect2.w >= rect1.x &&
		rect1.y + rect1.h >= rect2.y &&
		rect2.y + rect2.h >= rect1.y
		)
		return true;

	return false;
}

bool Collision::CheckCollisionEntity(SDL_Rect rect1, int x1, int y1, SDL_Rect rect2, int x2, int y2)
{
	if (
		x1 + rect1.w >= x2 &&
		x2 + rect2.w >= x1 &&
		y1 + rect1.h >= y2 &&
		y2 + rect2.h >= y1
		)
		return true;

	return false;
}

