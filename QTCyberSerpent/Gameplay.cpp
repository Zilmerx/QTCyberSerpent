#include "Gameplay.h"
#include "Utility.h"
#include "opencv2\highgui.hpp"
#include "CyberSerpent.h"

// PUBLIC

#pragma region Constructeur / Destructeur
Gameplay::Gameplay()
:m_Score{ 0 },
m_MaxScore{ 0 }
{
   m_IRobotPos = cv::Rect( 0, 0, 0, 0 );
}

Gameplay::~Gameplay()
{
}
#pragma endregion


void Gameplay::Initialize(CyberSerpent* link)
{
   m_Game = link;

   QRect rect = m_Game->m_QTCyberSerpent.m_LabelGameplay->geometry();
   m_ZoneJeu = cv::Rect(rect.x(), rect.y(), rect.width(), rect.height());

   m_ImageObstacle = cv::imread("ImageObstacle.bmp", CV_LOAD_IMAGE_UNCHANGED);
   m_ImagePoint = cv::imread("ImagePoint.bmp", CV_LOAD_IMAGE_UNCHANGED);
   m_ImageQueue = cv::imread("ImageQueue.bmp", CV_LOAD_IMAGE_UNCHANGED);
}

void Gameplay::Start(int MaxScore, int NbObstacles)
{
   m_Score = 0;
   m_MaxScore = MaxScore;

   fillWithRandRects(m_Obstacles, RectImage(m_ImageObstacle), NbObstacles);
   fillWithRandRects(m_Points, RectImage(m_ImagePoint), 5);
}

void Gameplay::Stop()
{
}

void Gameplay::MettreAJourInfos()
{
   m_IRobotPos.x = Utility::RandMinMax(0, m_ZoneJeu.width - m_IRobotPos.width);
   m_IRobotPos.y = Utility::RandMinMax(0, m_ZoneJeu.height - m_IRobotPos.height);

   if (!Utility::CvRect1ContainsRect2(m_ZoneJeu, m_IRobotPos))
   {
      // Perdu.
   }

   for (int i = 0; i < m_Obstacles.size(); ++i)
   {
      if (Utility::CvRect1TouchesRect2(m_IRobotPos, m_Obstacles[i]))
      {
         // Perdu.
      }
   }


   for (int i = 0; i < m_QueueSerpent.size(); ++i)
   {
      if (Utility::CvRect1TouchesRect2(m_IRobotPos, m_QueueSerpent[i]))
      {
         // Perdu.
      }
   }

   std::vector<int> toRemove;
   for (int i = 0; i < m_Points.size(); ++i)
   {
      if (Utility::CvRect1TouchesRect2(m_IRobotPos, m_Points[i]))
      {
         toRemove.push_back(i);

         m_Score++;

         VerifyScore(); // Check si gagné.
      }
   }
   for (int i = 0; i < toRemove.size(); ++i)
   {
      m_Points.erase(m_Points.begin() + toRemove[i] - i);
      m_Points.push_back(RandRect(m_ImagePoint));
   }
}

cv::Mat Gameplay::ModifierImage(cv::Mat&& mat)
{
   mat = Utility::DrawRectVectorOnMat(m_Obstacles, std::move(mat));
   mat = Utility::DrawRectVectorOnMat(m_Points, std::move(mat));
   mat = Utility::DrawRectVectorOnMat(m_QueueSerpent, std::move(mat));
   cv::rectangle(mat, cv::Point(m_IRobotPos.x, m_IRobotPos.y), cv::Point(m_IRobotPos.x + m_IRobotPos.width, m_IRobotPos.y + m_IRobotPos.height), cv::Scalar(0, 0, 200), 2);

   return mat;
}


// PRIVATE

void Gameplay::fillWithRandRects(std::vector<RectImage>& vec, RectImage rectimage, int amount)
{

   vec.clear();
   for (int i = 0; i < amount; ++i)
   {
      vec.push_back(RandRect(rectimage));
   }
}

RectImage Gameplay::RandRect(RectImage rectImage)
{
   RectImage nouveau(rectImage);
   nouveau.x = Utility::RandMinMax(0, m_ZoneJeu.width - nouveau.width);
   nouveau.y = Utility::RandMinMax(0, m_ZoneJeu.height - nouveau.height);
   return nouveau;
}

void Gameplay::VerifyScore()
{

}