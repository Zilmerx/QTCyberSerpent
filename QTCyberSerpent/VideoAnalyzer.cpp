#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"
#include "Settings.h"

VideoAnalyzer::VideoAnalyzer() 
   :RunAnalyse{ false },
   RunCaptureImage{ false }
{
}


void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;
   m_IRobotTemplate = cv::imread("templateIRobot.bmp", CV_32FC1);
   m_IRobotRect = RectCollision(m_IRobotTemplate);
}

void VideoAnalyzer::Start(int camNum)
{
   m_CamNumber = camNum;

   RunAnalyse = true;
   ThreadAnalyse = std::thread(&VideoAnalyzer::Analyse, this);

   RunCaptureImage = true;
   ThreadCaptureImage = std::thread(&VideoAnalyzer::CaptureImage, this);
}

void VideoAnalyzer::Stop()
{
   RunAnalyse = false;
   ThreadAnalyse.join();

   RunCaptureImage = false;
   ThreadCaptureImage.join();
}

//////////////////////////////////////////////////////////////////
// Threads
//////////////////////////////////////////////////////////////////

void VideoAnalyzer::CaptureImage()
{
   cv::VideoCapture cap;

   if (!IS_DEBUG)
      cap.open(std::atoi(m_CamNumber.c_str()));

   while (RunCaptureImage)
   {
      // Lecture d'une nouvelle image.
      if (!IS_DEBUG)
      {
         if (cap.isOpened())
         {
            cv::Mat mat;
            cap >> mat;
            m_ImageLue.Set(mat);
         }
      }
      else
      {
         m_ImageLue.Set(std::move(cv::imread("image.bmp", CV_32FC1)));
      }
   }
}

void VideoAnalyzer::Analyse()
{
   cv::Mat mat;

   while (RunAnalyse)
   {
      mat = m_ImageLue.Get();

      if (!Utility::MatIsNull(mat))
      {
         if (IS_DEBUG)
            mat = m_IRobotRect.Draw(std::move(mat));

         // Analyse de la position du IRobot dans l'image.
         if (!Utility::MatIsNull(m_IRobotTemplate))
         {
            int NbColTemplate = mat.cols - m_IRobotTemplate.cols + 1;
            int NbRangTemplate = mat.rows - m_IRobotTemplate.rows + 1;
            cv::Mat ImageResultat(NbRangTemplate, NbRangTemplate, CV_32FC1);

            double MinVal = 0, MaxVal = 0;
            cv::Point MinLoc, MaxLoc;

            cv::matchTemplate(mat, m_IRobotRect.m_Image, ImageResultat, CV_TM_CCOEFF);

            cv::normalize(ImageResultat, ImageResultat, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

            cv::minMaxLoc(ImageResultat, &MinVal, &MaxVal, &MinLoc, &MaxLoc);

            if (PRECISION_TEMPLATEMATCHING <= MaxVal)
            {
               if (!IS_DEBUG)
               {
                  m_IRobotRect.x = MaxLoc.x;
                  m_IRobotRect.y = MaxLoc.y;
               }

               m_Game->m_Gameplay.m_CompteurHorsZone = 0;

               // Update des informations en se servant de la nouvelle position du IRobot detectée.
               m_Game->m_Gameplay.MettreAJourInfos(m_IRobotRect);

               if (IS_DEBUG)
               {
                  cv::rectangle(mat, MaxLoc, cv::Point(MaxLoc.x + m_IRobotTemplate.cols, MaxLoc.y + m_IRobotTemplate.rows), cv::Scalar(0, 0, 200), 2);
               }

               // Modification de l'image en se servant des nouvelles informations acquises.
               mat = m_Game->m_Gameplay.ModifierImage(std::move(mat));

               // Affichage de l'image.
               m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(std::move(mat)));
            }
            else
            {
               m_Game->m_Gameplay.HorsZone();
            }
         }
      }
   }
}