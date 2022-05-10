#pragma once

class Stats
{
public:
	static int score;
	static int lifes;
	static bool victory;

	Stats();

	static void AddScore(int p_vl);
	static void SubtractScore(int p_vl);
	static void AddLife(int p_vl);
	static void SubttractLife(int p_vl);
	static void winGame();

	static bool isGameOver();

	//getters
	static int getScore();
	static int getLifes();
	static bool getVictory();
};
