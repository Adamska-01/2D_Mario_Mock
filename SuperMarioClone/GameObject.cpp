#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const char* p_textureSheet, Vector2D p_position)
	: position(p_position)
{
	objTexture = TextureManager::LoadTexture(p_textureSheet);
}

GameObject::GameObject(const char* p_textureSheet, Vector2D p_position, Camera* p_camera)
	: position(p_position), camera{ p_camera }
{
	objTexture = TextureManager::LoadTexture(p_textureSheet);
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	destRect.w = 32 * scale;
	destRect.h = 32 * scale;
	if (camera != nullptr)
	{
		destRect.x = position.x - camera->getRect().x;
		destRect.y = position.y - camera->getRect().y;
	}
	else
	{
		destRect.x = position.x;
		destRect.y = position.y;
	}
}

void GameObject::Down()
{
	int y = position.y + velocity.y;

	if (!map->isWall(position.x, y + (destRect.h - 1)) &&
		!map->isWall(position.x + (destRect.w - 1), y + ((destRect.h - 1) / 2)) &&
		!map->isWall(position.x + (destRect.w - 1), y + (destRect.h - 1)))
	{
		position.y = y;
	}
	else
		velocity.y = 0;
}

void GameObject::Up()
{
	int y = position.y - velocity.y;

	if (!map->isWall(position.x, y) &&
		!map->isWall(position.x + ((destRect.w - 1) / 2), y) &&
		!map->isWall(position.x + (destRect.w - 1), y))
	{
		position.y = y;
	}
	else
		velocity.y = 0;
}

void GameObject::Left()
{
	int x = position.x - velocity.x;

	if (!map->isWall(x, position.y) &&
		!map->isWall(x, position.y + ((destRect.h - 1) / 2)) &&
		!map->isWall(x, position.y + (destRect.h - 1)))
		position.x = x;
}

void GameObject::Right()
{
	int x = position.x + velocity.x;

	if (!map->isWall(x + (destRect.w - 1), position.y) &&
		!map->isWall(x + (destRect.w - 1), position.y + ((destRect.h - 1) / 2)) &&
		!map->isWall(x + (destRect.w - 1), position.y + (destRect.h - 1)))
		position.x = x;
}

void GameObject::Collision(SDL_Rect targetRect, Vector2D targetPos)
{
	if (position.y > initY) //down
	{
		if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
			targetRect, targetPos.x, targetPos.y))
		{
			velocity.y = 0;
			canKill = true;
		}
	}
	if (!canKill && (position.x > initX || position.x == initX)) //right
	{
		if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
			targetRect, targetPos.x, targetPos.y))
		{
			position = startPos;
			Stats::SubtractScore(100);
			Stats::SubttractLife(1);

			isDead = true;
		}
	}
	if (!canKill && (position.x < initX || position.x == initX)) //left
	{
		if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
			targetRect, targetPos.x, targetPos.y))
		{
			position = startPos;
			Stats::SubtractScore(100);
			Stats::SubttractLife(1);

			isDead = true;
		}
	}
	if (!canKill && (position.y < initY || position.x == initX)) //up
	{
		if (Collision::CheckCollisionEntity(destRect, position.x, position.y,
			targetRect, targetPos.x, targetPos.y))
		{
			position = startPos;
			Stats::SubtractScore(100);
			Stats::SubttractLife(1);

			isDead = true;	
		}
	}
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, NULL, &destRect);
}

SDL_Rect GameObject::getDestRect()
{
	return destRect;
}

Vector2D GameObject::getPosition()
{
	return position;
}

bool GameObject::IsDead()
{
	if (isDead)
		return true;

	return false;
}

bool GameObject::CanKIll()
{
	return canKill;
}

void GameObject::AddVelocity(Vector2D vel)
{
	velocity += vel;
}
