#pragma once
#include "Game.h"
#include "Vector2D.h"
#include <vector>
#include <utility>

class Map;
class Camera;

class GameObject
{
protected:
	Vector2D startPos;
	Vector2D position;
	Vector2D velocity;
	float scale;
	
	bool isDead = false;
	bool canKill = false;

	Map* map{ nullptr };
	Camera* camera{ nullptr };
	SDL_Texture* objTexture;
	SDL_Rect srcRect{}, destRect{};

	int speed = 100; //animation speed 
	int initX, initY; //Used for the collisions (previous Pos)
	
	std::vector<SDL_Texture*> Animations;
	std::vector<std::pair<SDL_Rect, int>> rectFrame;
	
public:
	GameObject(const char* p_textureSheet, Vector2D p_position); //no scrolling
	GameObject(const char* p_textureSheet, Vector2D p_position, Camera* p_camera);
	GameObject();
	~GameObject();

	virtual void Update();
	virtual void Down();
	virtual void Up();
	virtual void Left();
	virtual void Right();
	virtual void Collision(SDL_Rect targetRect, Vector2D targetPos);
	virtual void Render();
	
	SDL_Rect getDestRect();
	Vector2D getPosition();
	bool IsDead();
	bool CanKIll();

	void AddVelocity(Vector2D vel);
};

