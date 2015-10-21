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
      if (!Utility::CvRect1ContainsRect2(m_ZoneJeu, m_IRobotPos))
      {

      }

      for (cv::Rect rect : m_Obstacles)
      {
         if (Utility::CvRect1TouchesRect2(m_IRobotPos, rect))
         {

         }
      }

      for (cv::Rect rect : m_QueueSerpent)
      {
         if (Utility::CvRect1TouchesRect2(m_IRobotPos, rect))
         {

         }
      }

      for (cv::Rect rect : m_Points)
      {
         if (Utility::CvRect1TouchesRect2(m_IRobotPos, rect))
         {

         }
      }
   }
}

cv::Mat& Gameplay::ModifierImage(cv::Mat mat)
{
   auto func = [](std::vector<RectImage> vec, cv::Mat& mat)
   {
      for (RectImage rect : vec)
      {
         mat = Utility::DrawRectImageOnMat(rect, mat);
      }
   };

   func(m_Obstacles, mat);
   func(m_Points, mat);
   func(m_QueueSerpent, mat);

   return mat;
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
      vec.push_back(nouveau);
   }
}
