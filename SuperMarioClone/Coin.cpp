#include "Coin.h"
#include "Player.h"

Coin::Coin(Camera* p_camera, Map* p_map, Vector2D p_startPos)
{
	camera = p_camera;
	map = p_map;

	//load textures
	Animations.push_back(TextureManager::LoadTexture("Assets/Coin.png"));

	startPos = position = p_startPos;
	scale = 2;

	for (int i = 0; i < Animations.size(); i++)
	{
		rectFrame.push_back(std::make_pair(SDL_Rect(), 0));

		SDL_QueryTexture(Animations[i], NULL, NULL, &rectFrame[i].first.w, &rectFrame[i].first.h);
		rectFrame[i].first.x = 0;
		rectFrame[i].first.y = 0;
		rectFrame[i].second = 8;
		rectFrame[i].first.w /= rectFrame[i].second;
	}
}

Coin::~Coin()
{
	if (Animations.size() > 0)
	{
		for (int i = 0; i < Animations.size(); i++)
		{
			SDL_DestroyTexture(Animations[i]);
			Animations[i] = nullptr;
		}
		Animations.clear();
	}
}

void Coin::Update()
{
	if (!taken)
		position = startPos;

	//loops animations
	for (int i = 0; i < rectFrame.size(); i++)
	{
		rectFrame[i].first.x = rectFrame[i].first.w *
			static_cast<int>((SDL_GetTicks() / speed) % rectFrame[i].second);
	}

	//set pos and scale
	destRect.w = rectFrame[0].first.w * scale;
	destRect.h = rectFrame[0].first.h * scale;
	destRect.x = position.x - camera->getRect().x;
	destRect.y = position.y - camera->getRect().y;
}

void Coin::Render()
{
	SDL_RenderCopy(Game::renderer, Animations[0], &rectFrame[0].first, &destRect);
}

bool Coin::Collision(Player* p_player)
{
	if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
		p_player->getDestRect(), p_player->getPosition().x, p_player->getPosition().y))
	{
		taken = true;
		Stats::AddScore(score);
		
		return true;
	}

	return false;
}