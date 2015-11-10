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
}

Gameplay::~Gameplay()
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
   m_ZoneJeu = cv::Rect(rect.x(), rect.y(), rect.width(), rect.height());

   m_ImageObstacle = cv::imread("ImageObstacle.bmp", CV_32FC1);
   m_ImagePoint = cv::imread("ImagePoint.bmp", CV_32FC1);
   m_ImageQueue = cv::imread("ImageQueue.bmp", CV_32FC1);
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

void Gameplay::MettreAJourInfos(cv::Rect PositionIRobot)
{
	AddQueue(PositionIRobot);

   if (!Utility::CvRect1ContainsRect2(m_ZoneJeu, PositionIRobot))
   {
      // Perdu.
   }

   for (int i = 0; i < m_Obstacles.size(); ++i)
   {
      if (Utility::CvRect1TouchesRect2(PositionIRobot, m_Obstacles[i]))
      {
         // Perdu.
         m_Game->m_QTCyberSerpent.UI_PutMessageInList("COLLISION");
      }
   }


   for (int i = 0; i < m_QueueSerpent.size(); ++i)
   {
      if (Utility::CvRect1TouchesRect2(PositionIRobot, m_QueueSerpent[i]))
      {
         // Perdu.
      }
   }

   std::vector<int> toRemove;
   for (int i = 0; i < m_Points.size(); ++i)
   {
      if (Utility::CvRect1TouchesRect2(PositionIRobot, m_Points[i]))
      {
         toRemove.push_back(i);

         m_Score++;

         std::stringstream convert;
         convert << m_Score;
         std::string s = "SCORE" + convert.str();
         m_Game->m_QTCyberSerpent.UI_PutMessageInList(s);
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

void Gameplay::AddQueue(cv::Rect PositionIRobot)
{
	if ((std::chrono::steady_clock::now() - lastQueueUpdate) >= INTERVAL_QUEUE)
	{
		lastQueueUpdate = std::chrono::steady_clock::now();


		RectImage img = RectImage(m_ImageQueue);
		img.x = PositionIRobot.x;
		img.y = PositionIRobot.y;

		m_QueueSerpent.push_back(img);

		if (m_QueueSerpent.size() > 10)
		{
			m_QueueSerpent.erase(m_QueueSerpent.begin());
		}
	}
}