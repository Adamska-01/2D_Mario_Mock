#include "Player.h"
#include <iostream>


Player::Player(Input* p_input, Map* p_map)
	/*: GameObject("Assets/RunRight.png", 0, 0),*/ :input(p_input)
{
	map = p_map;

	//load textures
	Animations.push_back(TextureManager::LoadTexture("Assets/Idle.png"));
	Animations.push_back(TextureManager::LoadTexture("Assets/Run.png"));

	//init position and scale
	startPos.x = position.x = 32; startPos.y = position.y = 900;
	velocity.x = velocity.y = 4;
	initX = initY = 0;
	scale = 2;


	//set srcrect and corresponding frame number of animation
	for (int i = 0; i < Animations.size(); i++)
	{
		rectFrame.push_back(std::make_pair(SDL_Rect(), 0));

		SDL_QueryTexture(Animations[i], NULL, NULL, &rectFrame[i].first.w, &rectFrame[i].first.h);
		rectFrame[i].first.x = 0;
		rectFrame[i].first.y = 0;
		rectFrame[i].second = 8;
		rectFrame[i].first.w /= rectFrame[i].second;
	}

	/*rectFrame[0].first.x = 0;	rectFrame[1].first.x = 0;
	rectFrame[0].first.y = 0;	rectFrame[1].first.y = 0;
	rectFrame[0].first.w = 32;	rectFrame[1].first.w = 32;
	rectFrame[0].first.h = 32;	rectFrame[1].first.h = 32;
	rectFrame[0].second = 8;	rectFrame[1].second = 8;*/
}

Player::~Player()
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

	if (input != nullptr)
	{
		input = nullptr;
	}
}

void Player::Update()
{
	if(!isDead && !Stats::getVictory())
	{ 
		initX = position.x; initY = position.y;
		//input check
		if (input->KeyIsPressed(KEY_W) || input->KeyIsPressed(KEY_SPACE))
		{
			Jump(jumpForce);
		}
		if (input->KeyIsPressed(KEY_A))
		{
			Left();
		}
		if (input->KeyIsPressed(KEY_D))
		{
			Right();
		}

		Gravity();

		//loops animations
		for (int i = 0; i < rectFrame.size(); i++)
		{
			rectFrame[i].first.x = rectFrame[i].first.w *
				static_cast<int>((SDL_GetTicks() / GameObject::speed) % rectFrame[i].second);
		}

		//set pos and scale
		destRect.w = rectFrame[0].first.w * scale;
		destRect.h = rectFrame[0].first.h * scale;
		destRect.x = position.x;
		destRect.y = position.y;
	}
	if (Fall())
	{
		isDead = true;
		Stats::SubttractLife(1);
		position = startPos;
		if (Stats::getLifes() > 0)
			position = startPos;
	}
}

void Player::Up()
{
	int y = position.y - velocity.y;

	if (!map->isWall(position.x, y) && !map->isWall(position.x + (destRect.w - 1), y))
	{
		position.y = y;
	}
	else
	{
		velocity.y = 0;
	}
}

void Player::Down()
{
	int y = position.y + (-velocity.y);

	if (!map->isWall(position.x, y + (destRect.h - 1)) && !map->isWall(position.x + (destRect.w - 1), y + (destRect.h - 1)))
	{
		position.y = y;
	}
	else
	{
		velocity.y = 0;
	}
}

void Player::Jump(float jumpForce)
{
	if (map->isWall(position.x, position.y + (destRect.h)) || map->isWall(position.x + (destRect.w - 1), position.y + (destRect.h)))
	{
		velocity.y = jumpForce;
	}
}

void Player::Gravity()
{
	velocity.y -= map->getGravity();

	if (velocity.y > 0)
	{
		Up();
	}
	else
	{
		Down();
	}
}

void Player::Render(SDL_Rect m_dest)
{
	if (!isDead && !Stats::getVictory())
	{
		destRect = m_dest;

		if (input->KeyIsPressed(KEY_D)) //right
			SDL_RenderCopy(Game::renderer, Animations[1], &rectFrame[1].first, &destRect);
		else if (input->KeyIsPressed(KEY_A)) //flip right (left)
			SDL_RenderCopyEx(Game::renderer, Animations[1], &rectFrame[1].first, &destRect, 180, NULL, SDL_FLIP_VERTICAL);
		else //Idle
			SDL_RenderCopy(Game::renderer, Animations[0], &rectFrame[0].first, &destRect);

		canKill = false;
	}

	if (Stats::getLifes() > 0)
		isDead = false;
}

bool Player::Fall()
{
	if (position.x < 0 || position.y < 0 || position.x > map->getFullMap().w ||
		position.y > map->getFullMap().h)
		return true;

	return false;
}
