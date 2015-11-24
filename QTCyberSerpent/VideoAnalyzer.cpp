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

void VideoAnalyzer::Start(int camNum)
{
   cap.open(camNum);

   m_CaptureImage.Start();
   m_Affichage.Start();

   m_Gameplay.Start(m_Game->m_QTCyberSerpent.ui.lineEdit_MaxScore->text().toInt(), m_Game->m_QTCyberSerpent.ui.lineEdit_NbObstacles->text().toInt());
}

void VideoAnalyzer::Stop()
{
   m_Affichage.Stop();
   m_CaptureImage.Stop();

   m_Gameplay.Stop();
}

//////////////////////////////////////////////////////////////////
// Threads
//////////////////////////////////////////////////////////////////

void VideoAnalyzer::CaptureImage()
{
   // Lecture d'une nouvelle image.
   if (!IS_DEBUG)
   {
      if (cap.isOpened())
      {
         cv::Mat mat;
         cap >> mat;
         m_Gameplay.m_Input.Set(mat);
      }
   }
   else
   {
      m_Gameplay.m_Input.Set(std::move(cv::imread("image.bmp", CV_32FC1)));
   }
}

void VideoAnalyzer::Affichage()
{
   // Affichage de l'image.
   m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(std::move(m_Gameplay.m_Output.WaitGet())));
}