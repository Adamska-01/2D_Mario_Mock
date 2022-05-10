#pragma once
#include "Game.h"
#include <vector>
#include <string>


class Camera;


class Map
{
private:
	SDL_Rect srcRect{}, destRect{}, fullRect{};

	SDL_Texture* Tile;
	Camera* camera{ nullptr };

	std::vector<std::string> gridLayout;

	int width{ 0 }, height{ 0 };
	float gravity;

public:
	Map();
	~Map();

	void LoadMap(std::string path);
	inline void allocateCamera(Camera* m_camera) { camera = m_camera; };
	void DrawMap(bool isScrolling = false);

	bool isWall(int x, int y);

	void GetWidth();
	void GetHeight();
	float getGravity();
	SDL_Rect getFullMap();
};