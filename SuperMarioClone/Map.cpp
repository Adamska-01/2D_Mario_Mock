#include "Map.h"
#include "TextureManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Camera.h"

Map::Map()
{
	srcRect.w = 16;
	srcRect.h = 16;

	destRect.x = destRect.y = 0;

	destRect.w = 32;
	destRect.h = 32;

	Tile = TextureManager::LoadTexture("Assets/Map/Tiles.png");

	gravity = 1.5f;
}

Map::~Map()
{
	if (Tile != nullptr)
	{
		SDL_DestroyTexture(Tile);
		Tile = nullptr;
	}
}

void Map::LoadMap(std::string path)
{
	char tile;

	//x and y size of the file
	int sizeX = 0;
	int sizeY = 0;


	//create and open .txt file
	std::ifstream mapFile;
	mapFile.open(path);

	//get rows
	std::string line;
	while (getline(mapFile, line))
		sizeY++;


	//get columns
	std::stringstream s(line);
	char value;
	//while there's something in the line, ignore ','  and increase the number of columns
	while (s >> value)	if (value != ',') sizeX++;


	gridLayout.resize(sizeY);


	//start from beginning of the file 
	mapFile.clear();
	mapFile.seekg(0);


	//populate the array
	for (int y = 0; y < sizeY; y++)
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);

			gridLayout[y] += tile;

			mapFile.ignore();
		}


	GetWidth();		GetHeight();

	fullRect.w = width * destRect.w;
	fullRect.h = height * destRect.h;

	mapFile.close();
}


void Map::DrawMap(bool isScrolling)
{
	if (!isScrolling) //no longer continued 
	{
		int m_height = height;
		int m_width = width;
		char type = ' ';

		for (int row = 0; row < m_height; row++)
			for (int column = 0; column < m_width; column++)
			{
				destRect.x = column * destRect.w;
				destRect.y = row * destRect.h;

				switch (gridLayout[row][column])
				{
				case 'S':
					srcRect.x = srcRect.w * 12 + 12;
					srcRect.y = srcRect.h * 6 + 6;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'T':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'G':
					srcRect.x = srcRect.w * 3 + 3;
					srcRect.y = srcRect.h * 6 + 6;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'W':
					srcRect.x = srcRect.w * 11 + 11;
					srcRect.y = srcRect.h * 2 + 2;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				default:
					break;
				}
			}
	}
	else
	{
		int startHeight = camera->getRect().y / destRect.h;
		int m_height = camera->getRect().y + camera->getRect().h / destRect.h;
		if (m_height > height) //check boundaries
			m_height = height;

		int startWidth = camera->getRect().x / destRect.w;
		int m_width = camera->getRect().x + camera->getRect().w / destRect.w;
		if (m_width > width) //check boundaries
			m_width = width;

		char type = ' ';

		for (int row = startHeight; row < m_height; row++)
			for (int column = startWidth; column < m_width; column++)
			{
				destRect.x = column * destRect.w - camera->getRect().x;
				destRect.y = row * destRect.h - camera->getRect().y;

				switch (gridLayout[row][column])
				{
				case 'S':
					srcRect.x = srcRect.w * 12 + 12;
					srcRect.y = srcRect.h * 6 + 6;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '0':
					srcRect.x = srcRect.w * 12 + 12;
					srcRect.y = srcRect.h * 6 + 6;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'T':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'G':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 1 + 1;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'H':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 1 + 1;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'Y':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'V':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'B':
					srcRect.x = srcRect.w * 3 + 3;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'N':
					srcRect.x = srcRect.w * 4 + 4;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'M':
					srcRect.x = srcRect.w * 5 + 5;
					srcRect.y = srcRect.h * 0;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'J':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 1 + 1;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'I':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 2 + 2;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'O':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 2 + 2;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'L':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 2 + 2;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '?':
					srcRect.x = srcRect.w * 3 + 3;
					srcRect.y = srcRect.h * 2 + 2;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'K':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 3 + 3;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '.':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 3 + 3;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'R':
					srcRect.x = srcRect.w * 3 + 3;
					srcRect.y = srcRect.h * 3 + 3;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'A':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 3 + 3;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '1':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 4 + 4;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '3':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 4 + 4;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '4':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 5 + 5;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '5':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 5 + 5;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case '2':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 6 + 6;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'Q':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 7 + 7;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'F':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 7 + 7;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'D':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 7 + 7;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'Z':
					srcRect.x = srcRect.w * 0;
					srcRect.y = srcRect.h * 8 + 8;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'X':
					srcRect.x = srcRect.w * 1 + 1;
					srcRect.y = srcRect.h * 8 + 8;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'C':
					srcRect.x = srcRect.w * 2 + 2;
					srcRect.y = srcRect.h * 8 + 8;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'P':
					srcRect.x = srcRect.w * 3 + 3;
					srcRect.y = srcRect.h * 4 + 4;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				case 'W':
					srcRect.x = srcRect.w * 11 + 11;
					srcRect.y = srcRect.h * 2 + 2;
					TextureManager::Draw(Tile, srcRect, destRect);
					break;
				default:
					break;
				}
			}
	}
}

bool Map::isWall(int x, int y)
{
	//Prevents assertion error (vector out of bounds)
	if (x <0 || y < 0 || x > fullRect.w || y > fullRect.h)
		return false;

	if (gridLayout[y / destRect.h][x / destRect.w] == 'T' ||
		gridLayout[y / destRect.h][x / destRect.w] == 'I' ||
		gridLayout[y / destRect.h][x / destRect.w] == 'O' ||
		gridLayout[y / destRect.h][x / destRect.w] == 'K' ||
		gridLayout[y / destRect.h][x / destRect.w] == 'A' ||
		gridLayout[y / destRect.h][x / destRect.w] == 'M' ||
		gridLayout[y / destRect.h][x / destRect.w] == '0' ||
		gridLayout[y / destRect.h][x / destRect.w] == 'L')
	{
		return true;
	}

	return false;
}

void Map::GetWidth()
{
	width = gridLayout[0].length();
}

void Map::GetHeight()
{
	height = gridLayout.size();
}


float Map::getGravity()
{
	return gravity;
}

SDL_Rect Map::getFullMap()
{
	return fullRect;
}