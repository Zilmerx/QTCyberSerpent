#pragma once

#include <vector>
#include "Point2D.h"


class Gameplay
{

public:
	const static int MAPSIZE_X = 500;
	const static int MAPSIZE_Y = 500;


private:

	std::vector<Point2D> m_Obstacles;
	std::vector<Point2D> m_Points; // Contient les trucs à manger.
	int m_Score;

public:
	Gameplay();
	~Gameplay();

	void Start();

	void Stop();

private:
	// Mets "amount" Point2D dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
	void fillWithRandPoints(std::vector<Point2D>& tab, int amount);

};