#pragma once

#include <vector>
#include "opencv2\core.hpp"
#include "Utility.h"
#include "Collision.h"
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

   int m_CompteurHorsZone;

   const cv::Mat m_ImageObstacle;
   const cv::Mat m_ImagePoint;
   const cv::Mat m_ImageQueue;

   cv::Rect m_ZoneJeu;                    // Définis la zone de jeu.

   std::vector<RectCollision> m_Obstacles;    // Contient des obstacles.
   std::vector<CircleCollision> m_Points;     // Contient les trucs à manger.

   std::vector<RectCollision> m_QueueSerpent; // Contient la queue du serpent invisible.
   std::vector<RectCollision> m_QueueToPrint; // Contient la queue qui est affichée à l'utilisateur.

public:
	Gameplay();

   void Initialize(CyberSerpent* link);

	void Start(int MaxScore, int NbObstacles);

	void Stop();

   // Debug
   void UP();
   void RIGHT();
   void LEFT();
   void DOWN();

private:
   // Thread qui fais différentes analyses en se servant de la position du IRobot, puis détecte les collisions.
   // S'occupe aussi d'appeller les fonctions liées, en cas de collision.
   void MettreAJourInfos(cv::Rect PositionIRobot);

public:
   // Modifie l'image en se servant des informations stockées dans cette instance de Gameplay.
   cv::Mat ModifierImage(cv::Mat&& mat);
private:

   // Mets "amount" cv::Rect dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
   template<class T>
   void fillWithRand(std::vector<T>& vec, const T& col, int amount) const;

   RectCollision RandCollision(RectCollision RectCollision) const;

   CircleCollision RandCollision(CircleCollision circ) const;

   void IncrementScore();

   void HorsZone();

   void AddQueueInvis(cv::Rect PositionIRobot);

   int GetQueuePosFromScore(int score) const;
};