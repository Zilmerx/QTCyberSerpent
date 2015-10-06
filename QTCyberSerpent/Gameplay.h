#pragma once

#include <vector>
#include "Point2D.h"
#include "opencv2\core.hpp"
#include "Utility.h"

class Gameplay
{

public:
	const static int MAPSIZE_X = 500;
	const static int MAPSIZE_Y = 500;

   friend class VideoAnalyzer;

private:

   cv::Rect m_ZoneJeu;                   // Définis la zone de jeu.

   cv::Rect m_IRobotPos;

   std::vector<cv::Rect> m_Obstacles;   // Contient des obstacles.
   std::vector<cv::Rect> m_Points;      // Contient les trucs à manger.
   std::vector<cv::Rect> m_QueueSerpent;// Contient la queue du serpent.
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