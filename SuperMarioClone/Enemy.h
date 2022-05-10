#pragma once
#include "GameObject.h"


class Enemy : public GameObject
{
private:
	bool goLeft, switchDir;
	int scoreForKill;

public:
	Enemy();
	Enemy(Camera* p_camera, Map* p_map, Vector2D p_startPos);
	~Enemy();

	void Update() override;
	void Render() override;
	void Left() override;
	void Right() override;
	void Collision(Player* player);
	void AI();
	void Respawn();
};
