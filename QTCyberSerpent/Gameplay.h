#pragma once

#include <vector>
#include <mutex>

#include "opencv2\core.hpp"
#include "Utility.h"
#include "Collision.h"

#include "DoubleBuffer.h"
#include "ThreadWrapper.h"

class CyberSerpent;

class Gameplay
{
private:

   CyberSerpent* m_Game;

   int m_Score;
   int m_MaxScore;
   int m_MaxObstacles;

   int m_CompteurHorsZone;

   const cv::Mat m_ImageObstacle;
   const cv::Mat m_ImagePoint;
   const cv::Mat m_ImageQueue;
   const cv::Mat m_IRobotTemplate;

   RectCollision m_IRobotRect;

   cv::Rect m_ZoneJeu;                    // Définis la zone de jeu.

   std::vector<RectCollision> m_Cones;
   std::vector<RectCollision> m_Obstacles;    // Contient des obstacles.
   std::vector<CircleCollision> m_Points;     // Contient les trucs à manger.

   std::vector<RectCollision> m_QueueSerpent; // Contient la queue du serpent invisible.
   std::vector<RectCollision> m_QueueToPrint; // Contient la queue qui est affichée à l'utilisateur.

public:

   DoubleBuffer_Copie<cv::Mat> m_Input;
   DoubleBuffer_Copie<cv::Mat> m_Output;

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

   ThreadWrapper m_ImageSplitter;
   void Split();

   DoubleBuffer_Copie<cv::Mat> m_AAnalyser;
   DoubleBuffer_Copie<cv::Mat> m_AAfficher;

   // THREADS
   ThreadWrapper m_Detection;
   void Detection();

   std::mutex m_MutexCones;
   std::mutex m_MutexPos;

   ThreadWrapper m_MettreAJourInfos;
   void MettreAJourInfos();

   std::mutex m_MutexInfos;

   ThreadWrapper m_ModifierImage;
   void ModifierImage();

   // Fonctions
   void SpawnObstacles(cv::Rect PositionIRobot);
   void SpawnPoints(cv::Rect PositionIRobot);

   // Mets "amount" cv::Rect dans le tableau, qui ont un x,y entre "0" et "MAPSIZE_X"/"MAPSIZE_Y".
   template<class T>
   void fillWithRand(std::vector<T>& vec, const T& col, int amount) const;

   RectCollision RandCollision(RectCollision RectCollision) const;

   CircleCollision RandCollision(CircleCollision circ) const;

   void IncrementScore();

   void HorsZone();

   void AddQueueInvis();

   int GetQueuePosFromScore(int score) const;
};