#include "Enemy2.h"
#include "Player.h"

Enemy2::Enemy2()
{
}

Enemy2::Enemy2(Camera* p_camera, Map* p_map, Vector2D p_startPos)
{
	camera = p_camera;
	map = p_map;

	//load textures
	Animations.push_back(TextureManager::LoadTexture("Assets/Enemy2.png"));

	startPos = position = p_startPos;
	velocity = Vector2D(1, 1);
	scale = 0.5f;
	scoreForKill = 75;

	for (int i = 0; i < Animations.size(); i++)
	{
		rectFrame.push_back(std::make_pair(SDL_Rect(), 0));

		SDL_QueryTexture(Animations[i], NULL, NULL, &rectFrame[i].first.w, &rectFrame[i].first.h);
		rectFrame[i].first.x = 0;
		rectFrame[i].first.y = 0;
		rectFrame[i].second = 2;
		rectFrame[i].first.w /= rectFrame[i].second;
	}
}

Enemy2::~Enemy2()
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

void Enemy2::Update()
{
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

void Enemy2::Render(Vector2D playerPos)
{
	if (position.x >= playerPos.x) //Left
		SDL_RenderCopy(Game::renderer, Animations[0], &rectFrame[0].first, &destRect);
	else  //Right
		SDL_RenderCopyEx(Game::renderer, Animations[0], &rectFrame[0].first, &destRect, 180, NULL, SDL_FLIP_VERTICAL);

	velocity = Vector2D(1, 1);
}

void Enemy2::Collision(Player* player)
{
	//checks up

	if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
		player->getDestRect(), player->getPosition().x, player->getPosition().y))
	{
		position.y += 500;
		isDead = true;
		player->AddVelocity(Vector2D(0, 15));

		Stats::AddScore(scoreForKill);
	}
}

void Enemy2::AI(Vector2D playerPos)
{
	if (!isDead)
	{
		if (position.x > playerPos.x && position.dist(playerPos) < minDistance)
			Left();
		else if (position.x > startPos.x && position.dist(playerPos) > minDistance)
			Left();

		if (position.x < playerPos.x && position.dist(playerPos) < minDistance)
			Right();
		else if (position.x < startPos.x && position.dist(playerPos) > minDistance)
			Right();

		if (position.y > playerPos.y && position.dist(playerPos) < minDistance)
			Up();
		else if (position.y > startPos.y && position.dist(playerPos) > minDistance)
			Up();

		if (position.y < playerPos.y && position.dist(playerPos) < minDistance)
			Down();
		else if (position.y < startPos.y && position.dist(playerPos) > minDistance)
			Down();
	}
}

void Enemy2::Respawn()
{
	isDead = false;
	position = startPos;
}

