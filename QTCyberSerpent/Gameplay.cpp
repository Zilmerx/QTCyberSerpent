#include "Gameplay.h"
#include "Utility.h"
#include "opencv2\highgui.hpp"
#include "CyberSerpent.h"
#include "Settings.h"

// PUBLIC

#pragma region Constructeur / Destructeur
Gameplay::Gameplay()
   :m_Score{ 0 },
   m_MaxScore{ 0 },
   m_Game{ nullptr },
   m_ImageObstacle{ cv::imread("ImageObstacle.bmp", CV_32FC1) },
   m_ImagePoint{ cv::imread("ImagePoint.bmp", CV_32FC1) },
   m_ImageQueue{ cv::imread("ImageQueue.bmp", CV_32FC1) }
{
}

#pragma endregion

// Debug
void Gameplay::UP()
{
   m_Game->m_VideoAnalyzer.m_IRobotRect.y -= 5;
}
void Gameplay::RIGHT()
{
   m_Game->m_VideoAnalyzer.m_IRobotRect.x += 5;
}
void Gameplay::LEFT()
{
   m_Game->m_VideoAnalyzer.m_IRobotRect.x -= 5;
}
void Gameplay::DOWN()
{
   m_Game->m_VideoAnalyzer.m_IRobotRect.y += 5;
}

void Gameplay::Initialize(CyberSerpent* link)
{
   m_Game = link;

   QRect rect = m_Game->m_QTCyberSerpent.m_LabelGameplay->geometry();
   m_ZoneJeu = cv::Rect(0, 0, rect.width(), rect.height());
}

void Gameplay::Start(int MaxScore, int NbObstacles)
{
   m_Score = 0;
   m_MaxScore = MaxScore;
   m_QueueSerpent.reserve(GetQueuePosFromScore(m_MaxScore));
   m_QueueToPrint.reserve(GetQueuePosFromScore(m_MaxScore));

   fillWithRand<RectCollision>(m_Obstacles, RectCollision(m_ImageObstacle), NbObstacles);
   fillWithRand<CircleCollision>(m_Points, CircleCollision(m_ImagePoint), NB_POINTS_SIMULTANEE);
}

void Gameplay::Stop()
{
   // Ces deux premiers sont regénérés au Start();
   //m_Obstacles.clear();
   //m_Points.clear();

   m_QueueSerpent.clear();
   m_QueueToPrint.clear();
}

void Gameplay::MettreAJourInfos(cv::Rect PositionIRobot)
{
   AddQueueInvis(PositionIRobot);

   for (int i = 0; i < m_Obstacles.size(); ++i)
   {
      if (m_Obstacles[i].Touches(PositionIRobot))
      {
         m_Game->m_QTCyberSerpent.UI_AfficherLose();
      }
   }


   for (int i = NB_QUEUE_NOCOLLISION; i < m_QueueToPrint.size(); ++i)
   {
      if (m_QueueToPrint[i].Touches(PositionIRobot))
      {
         m_Game->m_QTCyberSerpent.UI_AfficherLose();
      }
   }

   std::vector<int> toRemove;
   for (int i = 0; i < m_Points.size(); ++i)
   {
      if (m_Points[i].Touches(PositionIRobot))
      {
         toRemove.push_back(i);

         IncrementScore(); // Check si gagné.
      }
   }
   for (int i = 0; i < toRemove.size(); ++i)
   {
      m_Points.erase(m_Points.begin() + toRemove[i] - i);
      m_Points.push_back(RandCollision(CircleCollision(m_ImagePoint)));
   }
}

cv::Mat Gameplay::ModifierImage(cv::Mat&& mat)
{
   mat = Collision::DrawVec(m_Obstacles, std::move(mat));
   mat = Collision::DrawVec(m_Points, std::move(mat));

   m_QueueToPrint.clear();
   for (int i = 0; i < m_Score; ++i)
   {
      int pos = m_QueueSerpent.size() - GetQueuePosFromScore(i) - 1;

      if (pos >= 0 && pos < m_QueueSerpent.size())
         m_QueueToPrint.push_back(m_QueueSerpent[pos]);
   }

   mat = Collision::DrawVec(m_QueueToPrint, std::move(mat));

   return mat;
}


// PRIVATE
template<class T>
void Gameplay::fillWithRand(std::vector<T>& vec, const T& col, int amount) const
{
   vec.clear();
   for (int i = 0; i < amount; ++i)
   {
      vec.push_back(RandCollision(col));
   }
}

RectCollision Gameplay::RandCollision(RectCollision rect) const
{
   RectCollision nouveau(rect);
   nouveau.x = Utility::RandMinMax(0, m_ZoneJeu.width - nouveau.width);
   nouveau.y = Utility::RandMinMax(0, m_ZoneJeu.height - nouveau.height);
   return nouveau;
}

CircleCollision Gameplay::RandCollision(CircleCollision circ) const
{
   CircleCollision nouveau(circ);
   nouveau.x = Utility::RandMinMax(0, m_ZoneJeu.width - (nouveau.rayon*2));
   nouveau.y = Utility::RandMinMax(0, m_ZoneJeu.height - (nouveau.rayon*2));
   return nouveau;
}

void Gameplay::IncrementScore()
{
   m_Score++;

   std::stringstream convert;
   convert << m_Score;
   std::string s = "SCORE" + convert.str();
   m_Game->m_QTCyberSerpent.UI_PutMessageInList(s);

   if (m_Score >= m_MaxScore)
   {
      m_Game->m_QTCyberSerpent.UI_AfficherWin();
   }
}

void Gameplay::HorsZone()
{
   m_CompteurHorsZone++;
   m_Game->m_QTCyberSerpent.UI_PutMessageInList("HORS ZONE");
   if (m_CompteurHorsZone >= NB_HORSZONE_MAX)
   {
      m_Game->m_QTCyberSerpent.UI_AfficherLose();
   }
}

void Gameplay::AddQueueInvis(cv::Rect PositionIRobot)
{
	RectCollision img = RectCollision(m_ImageQueue);
   Utility::PutRect1InCenterOfRect2(img, PositionIRobot);

	m_QueueSerpent.push_back(img);

   if (m_QueueSerpent.size() > GetQueuePosFromScore(m_MaxScore)) // Pour prévenir un éventuel overflow...
   {
      m_QueueSerpent.erase(m_QueueSerpent.begin());
   }
}

int Gameplay::GetQueuePosFromScore(int score) const
{
   return ((score + NB_QUEUEIMPRIM_SAUTE)*NB_QUEUE_SAUTE);
}