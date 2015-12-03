#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"
#include "Settings.h"

VideoAnalyzer::VideoAnalyzer() 
   :m_CaptureImage{ std::bind(&VideoAnalyzer::CaptureImage, this) },
   m_Affichage{ std::bind(&VideoAnalyzer::Affichage, this) }
{
}


void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;

   m_Gameplay.Initialize(linked);
}

bool VideoAnalyzer::Start(int camNum)
{
   cap = cv::VideoCapture(camNum);

   if (!cap.isOpened())
      return false;

   m_CaptureImage.Start();
   m_Affichage.Start();

   m_Gameplay.Start(m_Game->m_QTCyberSerpent.ui.lineEdit_MaxScore->text().toInt(), m_Game->m_QTCyberSerpent.ui.lineEdit_NbObstacles->text().toInt());

   return true;
}

void VideoAnalyzer::Stop()
{
   m_Affichage.Stop();
   m_CaptureImage.Stop();

   m_Gameplay.Stop();

   cap.release();
}

//////////////////////////////////////////////////////////////////
// Threads
//////////////////////////////////////////////////////////////////

void VideoAnalyzer::CaptureImage()
{
   cv::Mat frame;

   // Lecture d'une nouvelle image.
   if (cap.isOpened())
   {
      cap >> frame;
   }
   else
   {
      frame = cv::imread("image.bmp", IMAGETYPE);
   }

   if (!Utility::MatIsNull(frame))
   {
      m_Gameplay.m_Input.Set(std::move(frame));
   }
}

void VideoAnalyzer::Affichage()
{
   // Affichage de l'image.
   m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(std::move(m_Gameplay.m_Output.WaitGet())));
}