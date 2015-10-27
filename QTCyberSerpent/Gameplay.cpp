#include "Gameplay.h"
#include "Utility.h"
#include "opencv2\highgui.hpp"

// PUBLIC

#pragma region Constructeur / Destructeur
Gameplay::Gameplay()
: m_ZoneJeu{ 0, 0, MAPSIZE_X, MAPSIZE_Y },
m_IRobotPos{ 0, 0, 0, 0 },
m_Obstacles{},
m_Points{},
m_QueueSerpent{},
m_Score{ 0 },
m_MaxScore{ 0 },
RunMAJ{ false }
{

}

Gameplay::~Gameplay()
{
}
#pragma endregion


void Gameplay::Initialize()
{
   m_ImageObstacle = cv::imread("ImageObstacle.bmp", CV_LOAD_IMAGE_UNCHANGED);
   m_ImagePoint = cv::imread("ImagePoint.bmp", CV_LOAD_IMAGE_UNCHANGED);
   m_ImageQueue = cv::imread("ImageQueue.bmp", CV_LOAD_IMAGE_UNCHANGED);
}

void Gameplay::Start(int MaxScore, int NbObstacles)
{
   m_MaxScore = MaxScore;

   fillWithRandRects(m_Obstacles, RectImage(m_ImageObstacle), NbObstacles);

   RunMAJ = true;
   ThreadMAJ = std::thread(&Gameplay::MettreAJourInfos, this);
}

void Gameplay::Stop()
{
   RunMAJ = false;
   ThreadMAJ.join();
}

void Gameplay::MettreAJourInfos()
{
   while (RunMAJ)
   {
      fillWithRandRects(m_Obstacles, RectImage(m_ImageObstacle), 1);

      if (!Utility::CvRect1ContainsRect2(m_ZoneJeu, m_IRobotPos))
      {

      }

      if (m_Obstacles.size()> 0)
      {
         for (int i = 0; i < m_Obstacles.size(); ++i)
         {
            if (Utility::CvRect1TouchesRect2(m_IRobotPos, Utility::getValue_ThreadSafe(m_Obstacles, i)))
            {

            }
         }
      }

      if (m_QueueSerpent.size()> 0)
      {
         for (int i = 0; i < m_QueueSerpent.size(); ++i)
         {
            if (Utility::CvRect1TouchesRect2(m_IRobotPos, Utility::getValue_ThreadSafe(m_QueueSerpent, i)))
            {

            }
         }
      }

      if (m_Points.size()> 0)
      {
         for (int i = 0; i < m_Points.size(); ++i)
         {
            if (Utility::CvRect1TouchesRect2(m_IRobotPos, Utility::getValue_ThreadSafe(m_Points, i)))
            {

            }
         }
      }
   }
}

cv::Mat Gameplay::ModifierImage(cv::Mat&& mat)
{
   mat = Utility::DrawRectVectorOnMat(m_Obstacles, std::move(mat));
   mat = Utility::DrawRectVectorOnMat(m_Points, std::move(mat));
   return Utility::DrawRectVectorOnMat(m_QueueSerpent, std::move(mat));
}


// PRIVATE

void Gameplay::fillWithRandRects(std::vector<RectImage>& vec, RectImage rectimage, int amount)
{
   vec.clear();
   for (int i = 0; i < amount; ++i)
   {
      RectImage nouveau(rectimage);
      nouveau.x = Utility::RandMinMax(0, Gameplay::MAPSIZE_X - nouveau.width);
      nouveau.y = Utility::RandMinMax(0, Gameplay::MAPSIZE_Y - nouveau.height);
      Utility::push_back_ThreadSafe(vec, nouveau);
   }
}
