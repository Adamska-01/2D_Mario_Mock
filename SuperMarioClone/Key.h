#pragma once
#include "GameObject.h"

class Key : public GameObject
{
private:
	bool taken = false;
	int score = 100;

public:
	Key(Camera* p_camera, Map* p_map, Vector2D p_startPos);
	~Key();

	void Update() override;
	void Render() override;
	bool Collision(Player* p_player);
};