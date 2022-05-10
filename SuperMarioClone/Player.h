#pragma once
#include "GameObject.h"

class Input;

class Player : public GameObject
{
private:
	Input* input{ nullptr };

	float jumpForce = 28;

public:
	Player(Input* p_input, Map* p_map);
	~Player();

	void Update() override;
	void Up() override;
	void Down() override;
	void Jump(float jumpForce);
	void Gravity();
	void Render(SDL_Rect m_dest);
	bool Fall();
};