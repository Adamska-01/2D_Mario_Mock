#include "Enemy.h"
#include "Player.h"

Enemy::Enemy()
	:GameObject("Assets/Map/Grass.png", position)
{
	position = Vector2D(100, 100);
}

Enemy::Enemy(Camera* p_camera, Map* p_map, Vector2D p_startPos)
{
	camera = p_camera;
	map = p_map;

	//load textures
	Animations.push_back(TextureManager::LoadTexture("Assets/Enemy1.png"));

	startPos = position = p_startPos;
	velocity = Vector2D(2, 2);
	scale = .5f;
	scoreForKill = 50;

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

Enemy::~Enemy()
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

void Enemy::Update()
{
	AI();

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

void Enemy::Render()
{
	if (goLeft) //right
		SDL_RenderCopy(Game::renderer, Animations[0], &rectFrame[0].first, &destRect);
	else //flip right 
		SDL_RenderCopyEx(Game::renderer, Animations[0], &rectFrame[0].first, &destRect, 180, NULL, SDL_FLIP_VERTICAL);

	isDead = false;
}

void Enemy::Left()
{
	int x = position.x - velocity.x;

	if (!map->isWall(x, position.y) &&
		!map->isWall(x, position.y + (destRect.h - 1)))
	{
		position.x = x;

		switchDir = false;
	}
	else
	{
		switchDir = true;
	}
}

void Enemy::Right()
{
	int x = position.x + velocity.x;

	if (!map->isWall(x + (destRect.w - 1), position.y) &&
		!map->isWall(x + (destRect.w - 1), position.y + destRect.h - 1))
	{
		position.x = x;

		switchDir = false;
	}
	else
	{
		switchDir = true;
	}
}

void Enemy::Collision(Player* player)
{
	//checks up

	if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
		player->getDestRect(), player->getPosition().x, player->getPosition().y))
	{
		position.y += 600;
		player->AddVelocity(Vector2D(0, 15));
		isDead = true;

		Stats::AddScore(scoreForKill);
	}
}

void Enemy::AI()
{
	if (!isDead)
	{
		if (switchDir)
			goLeft = !goLeft;

		if (goLeft)
			Left();
		else
			Right();
	}
}

void Enemy::Respawn()
{
	isDead = false;
	position = startPos;
}
