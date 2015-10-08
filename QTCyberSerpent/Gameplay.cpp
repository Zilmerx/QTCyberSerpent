#include "Gameplay.h"
#include "Utility.h"

// PUBLIC

#pragma region Constructeur / Destructeur
Gameplay::Gameplay()
: m_ZoneJeu{ 0, 0, MAPSIZE_X, MAPSIZE_Y },
m_IRobotPos{ 0, 0, 0, 0 },
m_Obstacles{},
m_Points{},
m_QueueSerpent{},
m_Score{ 0 },
RunMAJ{ false }
{

}

Gameplay::~Gameplay()
{
}
#pragma endregion


void Gameplay::Initialize()
{

}

void Gameplay::Start()
{


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
      CollisionObstacle();
      CollisionLimiteJeu();
      CollisionPoint();
      CollisionQueue();
   }
}

// Events de collision.
void Gameplay::CollisionObstacle()
{
   for (cv::Rect rect : m_Obstacles)
   {
      if (Utility::CvRect1TouchesRect2(m_IRobotPos, rect))
      {

      }
   }
}

void Gameplay::CollisionLimiteJeu()
{
   if (!Utility::CvRect1ContainsRect2(m_ZoneJeu, m_IRobotPos))
   {

   }
}

void Gameplay::CollisionPoint()
{
   for (cv::Rect rect : m_Points)
   {
      if (Utility::CvRect1TouchesRect2(m_IRobotPos, rect))
      {

      }
   }
}

void Gameplay::CollisionQueue()
{
   for (cv::Rect rect : m_QueueSerpent)
   {
      if (Utility::CvRect1TouchesRect2(m_IRobotPos, rect))
      {

      }
   }
}



// PRIVATE

void Gameplay::fillWithRandRects(std::vector<cv::Rect>& tab, int amount)
{
   tab.clear();
   for (int i = 0; i < amount; ++i)
   {
      tab.push_back(cv::Rect());
      // Utility::RandMinMax(0, Gameplay::MAPSIZE_X), Utility::RandMinMax(0, Gameplay::MAPSIZE_Y)
   }
}
