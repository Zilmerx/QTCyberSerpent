#pragma once

#include <vector>
#include "opencv2\core.hpp"
#include "Utility.h"
#include <thread>

class Gameplay
{

public:
	const static int MAPSIZE_X = 500;
	const static int MAPSIZE_Y = 500;

   friend class VideoAnalyzer;

private:

   cv::Rect m_ZoneJeu;                  // D�finis la zone de jeu.

   cv::Rect m_IRobotPos;                // Zone occup�e par le robot pr�sentement.

   std::vector<cv::Rect> m_Obstacles;   // Contient des obstacles.
   std::vector<cv::Rect> m_Points;      // Contient les trucs � manger.
   std::vector<cv::Rect> m_QueueSerpent;// Contient la queue du serpent.
	int m_Score;


   // Thread qui fais diff�rentes analyses en se servant de la position du IRobot, puis d�tecte les collisions.
   // S'occupe aussi d'appeller les fonctions li�es, en cas de collision.
   bool RunMAJ;
   std::thread ThreadMAJ;
   void MettreAJourInfos();

   // Events de collision.
   void CollisionObstacle();

   void CollisionLimiteJeu();

   void CollisionPoint();

   void CollisionQueue();

public:
	Gameplay();
	~Gameplay();

   void Initialize();

	void Start();

	void Stop();

   // Modifie l'image en se servant des informations stock�es dans cette instance de Gameplay.
   void ModifierImage(cv::Mat& mat);

private:
	// Mets "amount" cv::Rect dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
   void fillWithRandRects(std::vector<cv::Rect>& tab, int amount);

};