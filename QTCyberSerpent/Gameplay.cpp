#include "Gameplay.h"
#include "Utility.h"
#include "opencv2\highgui.hpp"
#include "CyberSerpent.h"

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


void Gameplay::Initialize(CyberSerpent* link)
{
   m_Game = link;

   m_ImageObstacle = cv::imread("templateIRobot.bmp", CV_LOAD_IMAGE_UNCHANGED);
   m_ImagePoint = cv::imread("ImagePoint.bmp", CV_LOAD_IMAGE_UNCHANGED);
   m_ImageQueue = cv::imread("ImageQueue.bmp", CV_LOAD_IMAGE_UNCHANGED);
}

void Gameplay::Start(int MaxScore, int NbObstacles)
{
   m_MaxScore = MaxScore;

   m_NbObstacle = NbObstacles;
   fillWithRandRects(m_Obstacles, RectImage(m_ImageObstacle), m_NbObstacle);

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
      fillWithRandRects(m_Obstacles, RectImage(m_ImageObstacle), m_NbObstacle);

      std::this_thread::sleep_for(std::chrono::milliseconds(0));

      if (!Utility::CvRect1ContainsRect2(m_ZoneJeu, m_IRobotPos))
      {

      }

      {
         int cpt = 0;
         std::unique_lock<std::mutex> lock(m_Obstacles.m_Mutex);
         for (int i = 0; i < m_Obstacles.m_Vector.size(); ++i)
         {
            if (Utility::CvRect1TouchesRect2(m_IRobotPos, m_Obstacles.m_Vector[i]))
            {
               ++cpt;
            }
         }
         //m_Game->m_QTCyberSerpent.UI_PutMessageInList("COLLISION " + std::to_string(cpt));
      }

      {
         std::unique_lock<std::mutex> lock(m_QueueSerpent.m_Mutex);
         for (int i = 0; i < m_QueueSerpent.m_Vector.size(); ++i)
         {
            if (Utility::CvRect1TouchesRect2(m_IRobotPos, m_QueueSerpent.m_Vector[i]))
            {

            }
         }
      }

      {
         std::unique_lock<std::mutex> lock(m_Points.m_Mutex);
         for (int i = 0; i < m_Points.m_Vector.size(); ++i)
         {
            if (Utility::CvRect1TouchesRect2(m_IRobotPos, m_Points.m_Vector[i]))
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

void Gameplay::fillWithRandRects(MutexedVector<RectImage>& vec, RectImage rectimage, int amount)
{
   std::unique_lock<std::mutex> lock(vec.m_Mutex);
   vec.m_Vector.clear();
   for (int i = 0; i < amount; ++i)
   {
      RectImage nouveau(rectimage);
      nouveau.x = Utility::RandMinMax(0, Gameplay::MAPSIZE_X - nouveau.width);
      nouveau.y = Utility::RandMinMax(0, Gameplay::MAPSIZE_Y - nouveau.height);
      vec.m_Vector.push_back(nouveau);
   }
}
