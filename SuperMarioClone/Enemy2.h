#pragma once
#include "GameObject.h"

class Enemy2 : public GameObject
{
private:
	float minDistance = 300;
	int scoreForKill;

public:
	Enemy2();
	Enemy2(Camera* p_camera, Map* p_map, Vector2D p_startPos);
	~Enemy2();

	void Update() override;
	void Render(Vector2D playerPos);
	void Collision(Player* player);
	void AI(Vector2D playerPos);
	void Respawn();
};