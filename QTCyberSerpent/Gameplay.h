#pragma once

#include <vector>
#include "opencv2\core.hpp"
#include "Utility.h"
#include <thread>
#include "RectImage.h"

class Gameplay
{

public:
	const static int MAPSIZE_X = 250;
   const static int MAPSIZE_Y = 250;

   friend class VideoAnalyzer;

private:
   int m_MaxScore;

   cv::Mat m_ImageObstacle;
   cv::Mat m_ImagePoint;
   cv::Mat m_ImageQueue;

   cv::Rect m_ZoneJeu;                       // D�finis la zone de jeu.

   cv::Rect m_IRobotPos;                     // Zone occup�e par le robot pr�sentement.

   std::vector<RectImage> m_Obstacles;   // Contient des obstacles.
   std::vector<RectImage> m_Points;      // Contient les trucs � manger.
   std::vector<RectImage> m_QueueSerpent;// Contient la queue du serpent.
	int m_Score;

public:
	Gameplay();
	~Gameplay();

   void Initialize();

	void Start(int MaxScore, int NbObstacles);

	void Stop();

   // Modifie l'image en se servant des informations stock�es dans cette instance de Gameplay.
   cv::Mat& ModifierImage(cv::Mat mat);
private:

   // Thread qui fais diff�rentes analyses en se servant de la position du IRobot, puis d�tecte les collisions.
   // S'occupe aussi d'appeller les fonctions li�es, en cas de collision.
   bool RunMAJ;
   std::thread ThreadMAJ;
   void MettreAJourInfos();

	// Mets "amount" cv::Rect dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
   void fillWithRandRects(std::vector<RectImage>& vec, RectImage rectimage, int amount);

};