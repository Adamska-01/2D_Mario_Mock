#include "Stats.h"

int Stats::score = 0;
int Stats::lifes = 0;
bool Stats::victory = false;

Stats::Stats()
{
	score = 0;
	lifes = 3;
	victory = false;
}

void Stats::AddScore(int p_vl)
{
	score += p_vl;
}

void Stats::SubtractScore(int p_vl)
{
	score -= p_vl;
}

void Stats::AddLife(int p_vl)
{
	lifes += 1;
}

void Stats::SubttractLife(int p_vl)
{
	lifes -= 1;
}

void Stats::winGame()
{
	victory = true;
}

bool Stats::isGameOver()
{
	if (lifes <= 0)
		return true;

	return false;
}

int Stats::getScore()
{
	return score;
}

int Stats::getLifes()
{
	return lifes;
}

bool Stats::getVictory()
{
	return victory;
}
