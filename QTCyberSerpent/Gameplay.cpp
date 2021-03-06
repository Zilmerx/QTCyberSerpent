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
   m_ImageObstacle{ TryImread("ImageObstacle.bmp") },
   m_ImagePoint{ TryImread("ImagePoint.bmp") },
   m_ImageQueue{ TryImread("ImageQueue.bmp") },
   m_IRobotTemplate{ TryImread("templateIRobot.bmp") },
   m_ImageSplitter{ std::bind(&Gameplay::Split, this) },
   m_Detection{ std::bind(&Gameplay::Detection ,this) },
   m_MettreAJourInfos{ std::bind(&Gameplay::MettreAJourInfos, this) },
   m_ModifierImage{ std::bind(&Gameplay::ModifierImage, this) }
{
   m_IRobot.pos.x = -1;
   m_IRobot.pos.y = -1;

   m_IRobot = CircleCollision(m_IRobotTemplate);
}

#pragma endregion

// Debug
void Gameplay::UP()
{
   m_IRobot.pos.y -= 5;
}
void Gameplay::RIGHT()
{
   m_IRobot.pos.x += 5;
}
void Gameplay::LEFT()
{
   m_IRobot.pos.x -= 5;
}
void Gameplay::DOWN()
{
   m_IRobot.pos.y += 5;
}

void Gameplay::Initialize(CyberSerpent* link)
{
   m_Game = link;

   QRect rect = m_Game->m_QTCyberSerpent.m_LabelGameplay->geometry();
   m_ZoneJeu = cv::Rect(0, 0, rect.width(), rect.height());
}

void Gameplay::Start(int MaxScore, int NbObstacles)
{
   m_IRobot.pos.x = -1;
   m_IRobot.pos.y = -1;

   m_Score = 0;
   m_MaxScore = MaxScore;
   m_MaxObstacles = NbObstacles;

   m_QueueSerpent.reserve(GetQueuePosFromScore(m_MaxScore));
   m_QueueToPrint.reserve(GetQueuePosFromScore(m_MaxScore));

   m_ImageSplitter.Start();
   m_Detection.Start();
   m_MettreAJourInfos.Start();
   m_ModifierImage.Start();
}

void Gameplay::Stop()
{
   m_ImageSplitter.Stop();
   m_Detection.Stop();
   m_MettreAJourInfos.Stop();
   m_ModifierImage.Stop();

   m_Input.Clear();
   m_Output.Clear();
   m_AAfficher.Clear();
   m_AAnalyser.Clear();

   m_Cones.clear();
   m_Obstacles.clear();
   m_Points.clear();
   m_QueueSerpent.clear();
   m_QueueToPrint.clear();
}


// PRIVATE

void Gameplay::SpawnObstacles(cv::Rect PositionIRobot)
{
   while (m_Obstacles.size() < m_MaxObstacles)
   {
      RectCollision obstacle;

      bool stop = false;
      while (!stop)
      {
         stop = true;
         obstacle = RandCollision(RectCollision(m_ImageObstacle));

         if (obstacle.Touches(PositionIRobot))
         {
            stop = false;
         }
      }

      m_Obstacles.push_back(obstacle);
   }
}

void Gameplay::SpawnPoints(cv::Rect PositionIRobot)
{
   while (m_Points.size() < NB_POINTS_SIMULTANEE)
   {
      CircleCollision point;

      bool stop = false;
      while (!stop)
      {
         stop = true;
         point = RandCollision(CircleCollision(m_ImagePoint));

         for (const RectCollision& rect : m_Obstacles)
         {
            if (rect.Touches(point))
            {
               stop = false;
               break;
            }
         }

         {
            std::lock_guard<std::mutex> lock(m_MutexCones);
            for (const RectCollision& rect : m_Cones)
            {
               if (rect.Touches(point))
               {
                  stop = false;
                  break;
               }
            }
         }

         if (point.Touches(PositionIRobot))
         {
            stop = false;
         }
      }

      m_Points.push_back(point);
   }
}

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
   nouveau.pos.x = Utility::RandMinMax(0, m_ZoneJeu.width - nouveau.width);
   nouveau.pos.y = Utility::RandMinMax(0, m_ZoneJeu.height - nouveau.height);
   return nouveau;
}

CircleCollision Gameplay::RandCollision(CircleCollision circ) const
{
   CircleCollision nouveau(circ);
   nouveau.pos.x = Utility::RandMinMax(0, m_ZoneJeu.width - (nouveau.rayon * 2));
   nouveau.pos.y = Utility::RandMinMax(0, m_ZoneJeu.height - (nouveau.rayon * 2));
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

void Gameplay::AddQueueInvis()
{
   RectCollision img = RectCollision(m_ImageQueue);
   Utility::PutRect1InCenterOfRect2<RectCollision>(img, m_IRobot);

	m_QueueSerpent.push_back(img);

   if (m_QueueSerpent.size() > GetQueuePosFromScore(m_MaxScore)) // Pour pr�venir un �ventuel overflow...
   {
      m_QueueSerpent.erase(m_QueueSerpent.begin());
   }
}

int Gameplay::GetQueuePosFromScore(int score) const
{
   return ((score + NB_QUEUEIMPRIM_SAUTE)*NB_QUEUE_SAUTE);
}

void CalibrerTemplateMatch(double MaxVal)
{
   if (!TEMPLATEMATCHING_CALIBRE)
   {
      PRECISION_TEMPLATEMATCHING = MaxVal - 0.15;
      TEMPLATEMATCHING_CALIBRE = true;
   }
}







//////////////////////////////////////////////////////////////////////////////////////////
//////    THREADS
//////////////////////////////////////////////////////////////////////////////////////////

void Gameplay::Split()
{
   cv::Mat mat1, mat2;
   
   mat1 = m_Input.Get();
   mat1.copyTo(mat2);

   m_AAnalyser.Set(std::move(mat1));
   m_AAfficher.Set(std::move(mat2));
}

void Gameplay::Detection()
{
   cv::Mat mat = m_AAnalyser.WaitGet();

   if (!Utility::MatIsNull(mat))
   {
      cv::GaussianBlur(mat, mat, cv::Size(3, 3), 3.0);

      // Analyse de la position du IRobot dans l'image.
      if (!Utility::MatIsNull(m_IRobotTemplate))
      {
         int NbColTemplate = mat.cols - m_IRobotTemplate.cols + 1;
         int NbRangTemplate = mat.rows - m_IRobotTemplate.rows + 1;
         cv::Mat ImageResultat(NbRangTemplate, NbColTemplate, mat.type());

         double MinVal = 0, MaxVal = 0;
         cv::Point MinLoc, MaxLoc;

         cv::matchTemplate(mat, m_IRobotTemplate, ImageResultat, CV_TM_CCOEFF);

         cv::normalize(ImageResultat, ImageResultat, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

         cv::minMaxLoc(ImageResultat, &MinVal, &MaxVal, &MinLoc, &MaxLoc);

         CalibrerTemplateMatch(MaxVal);

         if (PRECISION_TEMPLATEMATCHING <= MaxVal)
         {
            if (!IS_DEBUG)
            {
               std::lock_guard<std::mutex> lock(m_MutexPos);
               m_IRobot.pos.x = MaxLoc.x;
               m_IRobot.pos.y = MaxLoc.y;
            }
            else
            {
               HorsZone();
               std::lock_guard<std::mutex> lock(m_MutexPos);
               m_IRobot.pos.x = -1;
               m_IRobot.pos.y = -1;
            }

            m_CompteurHorsZone = 0;
         }
      }

      cv::Mat inrange_output;

      cv::inRange(mat, COULEUR_CONE_MIN, COULEUR_CONE_MAX, inrange_output);

      std::vector<std::vector<cv::Point>> contours;
      findContours(inrange_output, contours, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

      std::vector<std::vector<cv::Point>> contours_poly(contours.size());

      {
         std::lock_guard<std::mutex> lock(m_MutexCones);
         m_Cones.clear();
         for (int i = 0; i < contours.size(); i++)
         {
            approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
            m_Cones.push_back(RectCollision(cv::boundingRect(cv::Mat(contours_poly[i]))));
         }
      }
   }
}

void Gameplay::MettreAJourInfos()
{
   while (m_IRobot.pos.x == -1 || m_IRobot.pos.y == -1);

   std::lock_guard<std::mutex> infolock(m_MutexInfos);

   std::unique_lock<std::mutex> poslock(m_MutexPos);
   const CircleCollision IRobotRect_local = m_IRobot;
   poslock.unlock();

   if (IRobotRect_local.pos.x == -1 || IRobotRect_local.pos.y == -1) return;

   for (int i = 0; i < m_Obstacles.size(); ++i)
   {
      if (m_Obstacles[i].Touches(IRobotRect_local))
      {
         m_Game->m_QTCyberSerpent.UI_AfficherLose(); // Weird bug puts obstacles position and puts it in m_IRobotRect.
      }
   }

   {
      std::lock_guard<std::mutex> lock(m_MutexCones);
      for (int i = 0; i < m_Cones.size(); ++i)
      {
         if (m_Cones[i].Touches(IRobotRect_local))
         {
            m_Game->m_QTCyberSerpent.UI_AfficherLose();
         }
      }
   }

   for (int i = NB_QUEUE_NOCOLLISION; i < m_QueueToPrint.size(); ++i)
   {
      if (m_QueueToPrint[i].Touches(IRobotRect_local))
      {
         m_Game->m_QTCyberSerpent.UI_AfficherLose();
      }
   }

   for (auto it = m_Points.begin(); it != m_Points.end();)
   {
      if (it->Touches(IRobotRect_local))
      {
         it = m_Points.erase(it);

         IncrementScore(); // Check si gagn�.
      }
      else ++it;
   }

   m_QueueToPrint.clear();
   for (int i = 0; i < m_Score; ++i)
   {
      int pos = m_QueueSerpent.size() - GetQueuePosFromScore(i) - 1;

      if (pos >= 0 && pos < m_QueueSerpent.size())
         m_QueueToPrint.push_back(m_QueueSerpent[pos]);
   }

   SpawnPoints(IRobotRect_local);
   SpawnObstacles(IRobotRect_local);
}

void Gameplay::ModifierImage()
{
   std::lock_guard<std::mutex> lock(m_MutexInfos);

   cv::Mat mat;
   AddQueueInvis();

   mat = m_AAfficher.WaitGet();

   if (!Utility::MatIsNull(mat))
   {
      mat = Collision::DrawVec(m_Obstacles, std::move(mat));

      if (BOXES_DETECTION)
      {
         std::lock_guard<std::mutex> lock(m_MutexCones);
         for (const RectCollision rect : m_Cones)
         {
            cv::rectangle(mat, rect, cv::Scalar(255, 0, 0), 2);
         }
      }

      try
      {
         mat = Collision::DrawVec(m_Points, std::move(mat));
      }
      catch (cv::Exception) // Exception bizarre juste avec les points...
      {
      }

      if (IS_DEBUG)
      {
         mat = m_IRobot.Draw(std::move(mat));
      }
      else if (BOXES_DETECTION)
      {
         cv::circle(mat, m_IRobot.Center(), m_IRobot.rayon, cv::Scalar(255, 0, 0), 2);
      }

      m_Output.Set(std::move(Collision::DrawVec(m_QueueToPrint, std::move(mat))));
   }
}

cv::Mat Gameplay::TryImread(std::string&& path) const
{
   cv::Mat mat;
   for (int i = 0; i < 5; ++i)
   {
      mat = cv::imread(path, IMAGETYPE);
      if (!Utility::MatIsNull(mat))
      {
         return mat;
      }
   }
   exit(1);
   return mat;
}