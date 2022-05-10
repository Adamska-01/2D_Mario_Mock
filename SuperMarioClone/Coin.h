#pragma once
#include "GameObject.h"

class Coin : public GameObject
{
private:
	bool taken = false;
	int score = 100;

public:
	Coin(Camera* p_camera, Map* p_map, Vector2D p_startPos);
	~Coin();

	void Update() override;
	void Render() override;
	bool Collision(Player* player);
};