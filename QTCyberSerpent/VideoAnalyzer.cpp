#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"
#include "Settings.h"

VideoAnalyzer::VideoAnalyzer() 
   :RunDo{ false }
{
}

VideoAnalyzer::~VideoAnalyzer()
{
}

void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;

   m_IRobotTemplate = cv::imread("templateIRobot.bmp", CV_32FC1);

   m_IRobotRect = RectImage(std::move(cv::imread("templateIRobot.bmp", CV_32FC1)));
}

void VideoAnalyzer::Start(int camNum)
{
   m_CamNumber = camNum;

   RunDo = true;
   ThreadDo = std::thread(&VideoAnalyzer::Do, this);
}

void VideoAnalyzer::Stop()
{
   RunDo = false;
   ThreadDo.join();
}

//////////////////////////////////////////////////////////////////
// Threads
//////////////////////////////////////////////////////////////////


void VideoAnalyzer::Do()
{
   cv::Mat mat;
   cv::VideoCapture cap(m_CamNumber);
   while (RunDo)
   {
      // Lecture d'une nouvelle image.
      if (cap.isOpened())
      {
         cap >> mat;
      }
      else
      {
         cv::imread("image.bmp", CV_32FC1).copyTo(mat);
      }

      if (!Utility::MatIsNull(mat))
      {
         // Debug
         mat = Utility::DrawRectImageOnMat(m_IRobotRect, std::move(mat));

         // Analyse de la position du IRobot dans l'image.
         if (!Utility::MatIsNull(m_IRobotTemplate))
         {
            int NbColTemplate = mat.cols - m_IRobotTemplate.cols + 1;
            int NbRangTemplate = mat.rows - m_IRobotTemplate.rows + 1;
            cv::Mat ImageResultat(NbRangTemplate, NbRangTemplate, CV_32FC1);

            double MinVal = 0, MaxVal = 0;
            cv::Point MinLoc, MaxLoc;

            cv::matchTemplate(mat, m_IRobotRect.m_Image, ImageResultat, CV_TM_CCOEFF);

            cv::minMaxLoc(ImageResultat, &MinVal, &MaxVal, &MinLoc, &MaxLoc);

            cv::rectangle(mat, MaxLoc, cv::Point(MaxLoc.x + m_IRobotTemplate.cols, MaxLoc.y + m_IRobotTemplate.rows), cv::Scalar(0, 0, 200), 2);
            // Debug
            //m_IRobotRect.x = MaxLoc.x;
            //m_IRobotRect.y = MaxLoc.y;
         }

         // Update des informations en se servant de la nouvelle position du IRobot detectée.
         m_Game->m_Gameplay.MettreAJourInfos(m_IRobotRect);

         // Modification de l'image en se servant des nouvelles informations acquises.
         mat = m_Game->m_Gameplay.ModifierImage(std::move(mat));

         // Affichage de l'image.
         m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(std::move(mat)));
      }
   }
}