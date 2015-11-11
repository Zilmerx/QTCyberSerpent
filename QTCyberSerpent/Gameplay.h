#pragma once

#include <vector>
#include "opencv2\core.hpp"
#include "Utility.h"
#include <thread>
#include "RectImage.h"
#include <atomic>
#include "MutexedVector.h"
#include "VideoAnalyzer.h"

class CyberSerpent;

class Gameplay
{
public:
   friend class VideoAnalyzer;

private:
   CyberSerpent* m_Game;

   int m_Score;
   int m_MaxScore;

   cv::Mat m_ImageObstacle;
   cv::Mat m_ImagePoint;
   cv::Mat m_ImageQueue;

   cv::Rect m_ZoneJeu;                    // D�finis la zone de jeu.

   std::vector<RectImage> m_Obstacles;    // Contient des obstacles.
   std::vector<RectImage> m_Points;       // Contient les trucs � manger.

   std::vector<RectImage> m_QueueSerpent; // Contient la queue du serpent invisible.
   std::vector<RectImage> m_QueueToPrint; // Contient la queue qui est affich�e � l'utilisateur.

public:
	Gameplay();
	~Gameplay();

   void Initialize(CyberSerpent* link);

	void Start(int MaxScore, int NbObstacles);

	void Stop();

   // Debug
   void UP();
   void RIGHT();
   void LEFT();
   void DOWN();

   // Modifie l'image en se servant des informations stock�es dans cette instance de Gameplay.
   cv::Mat ModifierImage(cv::Mat&& mat);
private:

   // Thread qui fais diff�rentes analyses en se servant de la position du IRobot, puis d�tecte les collisions.
   // S'occupe aussi d'appeller les fonctions li�es, en cas de collision.
   void MettreAJourInfos(cv::Rect PositionIRobot);

	// Mets "amount" cv::Rect dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
   void fillWithRandRects(std::vector<RectImage>& vec, RectImage rectimage, int amount);

   RectImage RandRect(RectImage rectImage);

   void IncrementScore();

   void AddQueueInvis(cv::Rect PositionIRobot);
};