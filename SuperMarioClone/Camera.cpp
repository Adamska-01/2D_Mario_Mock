#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
}

Camera::Camera(Player* m_player, Map* m_map)
	:player(m_player), map(m_map)
{
	SDL_GetRendererOutputSize(Game::renderer, &screenW, &screenH);

	cameraRect = { 0,0, screenW, screenH };
}

Camera::~Camera()
{
	if (map != nullptr)
	{
		delete map;
		map = nullptr;
	}
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
}

void Camera::Update()
{
	cameraRect.x = (player->getDestRect().x + (player->getDestRect().h / 2)) - cameraRect.w / 2;
	cameraRect.y = (player->getDestRect().y + (player->getDestRect().h / 2)) - cameraRect.h / 2;

	//Avoid player being always in the middle of the screen
	if (cameraRect.x < 0)
		cameraRect.x = 0;
	if (cameraRect.y < 0)
		cameraRect.y = 0;

	//same as up, but checks the end of the map
	if (cameraRect.x > map->getFullMap().w - cameraRect.w)
		cameraRect.x = map->getFullMap().w - screenW;
	if (cameraRect.y > map->getFullMap().h - cameraRect.h)
		cameraRect.y = map->getFullMap().h - screenH;
}

SDL_Rect Camera::getDrawingRect()
{
	SDL_Rect drawingRect = { player->getDestRect().x - cameraRect.x,
							player->getDestRect().y - cameraRect.y,
							player->getDestRect().w, player->getDestRect().h };

	return drawingRect;
}

SDL_Rect Camera::getRect()
{
	return cameraRect;
}
