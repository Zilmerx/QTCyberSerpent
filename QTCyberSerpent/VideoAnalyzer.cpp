#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"

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

   m_IRobotTemplate = cv::imread("templateIRobot.bmp", CV_LOAD_IMAGE_UNCHANGED);

   m_IRobotRect = std::make_unique<RectImage>(m_IRobotTemplate);
   m_Game->m_Gameplay.m_IRobotPos.x = m_IRobotRect->x = 150;
   m_Game->m_Gameplay.m_IRobotPos.y = m_IRobotRect->y = 150;
   m_Game->m_Gameplay.m_IRobotPos.width = m_IRobotTemplate.cols;
   m_Game->m_Gameplay.m_IRobotPos.height = m_IRobotTemplate.rows;
}

void VideoAnalyzer::Start(std::string path)
{
   m_CamImagePath = path;

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
   cv::VideoCapture cap(0);
   while (RunDo)
   {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      // Lecture d'une nouvelle image.
      if (cap.isOpened())
      {
         cap >> mat;
      }
      else
      {
         cv::imread(m_CamImagePath, CV_LOAD_IMAGE_UNCHANGED).copyTo(mat);
      }

      if (!Utility::MatIsNull(mat))
      {
         // Analyse de la position du IRobot dans l'image.
         if (Utility::MatIsNull(m_IRobotTemplate))
         {
            double MinVal, MaxVal;
            cv::Point MinLoc, MaxLoc;

            cv::Mat& Source = mat.clone();

            cv::matchTemplate(Source, m_IRobotTemplate, Source, CV_TM_CCORR);
            cv::minMaxLoc(Source, &MinVal, &MaxVal, &MinLoc, &MaxLoc, 0);

            if (MaxVal >= PRECISION_TEMPLATEMATCHING())
            {
               m_Game->m_Gameplay.m_IRobotPos.x = MaxLoc.x;
               m_Game->m_Gameplay.m_IRobotPos.y = MaxLoc.y;
            }
         }

         // Update des informations en se servant de la nouvelle position du IRobot detectée.
         m_Game->m_Gameplay.MettreAJourInfos();

         // Modification de l'image en se servant des nouvelles informations acquises.
         mat = Utility::DrawRectImageOnMat(*m_IRobotRect.get(), std::move(mat));
         mat = m_Game->m_Gameplay.ModifierImage(std::move(mat));

         // Affichage de l'image.
         m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(std::move(mat)));
      }
   }
}