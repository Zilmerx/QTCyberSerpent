#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"

VideoAnalyzer::VideoAnalyzer() 
	:RunLecture{ false }, 
   RunTrouverRobot{ false },
   RunCreerImage{ false },
	RunAffichage{ false }
{
}

VideoAnalyzer::~VideoAnalyzer()
{
}

void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;

   while (Utility::MatIsNull(m_IRobotTemplate))
   {
      m_IRobotTemplate = cv::imread("ImageObstacle.bmp", CV_LOAD_IMAGE_UNCHANGED);
   }

   m_IRobotRect = std::make_unique<RectImage>(m_IRobotTemplate);
   m_Game->m_Gameplay.m_IRobotPos.x = m_IRobotRect->x = 150;
   m_Game->m_Gameplay.m_IRobotPos.y = m_IRobotRect->y = 150;
   m_Game->m_Gameplay.m_IRobotPos.width = m_IRobotTemplate.cols;
   m_Game->m_Gameplay.m_IRobotPos.height = m_IRobotTemplate.rows;
}

void VideoAnalyzer::Start(std::string path)
{
   m_CamImagePath = path;

	RunLecture = true;
	ThreadLecture = std::thread(&VideoAnalyzer::LireFichier, this);

   RunTrouverRobot = true;
   ThreadTrouverRobot = std::thread(&VideoAnalyzer::TrouverRobot, this);

   RunCreerImage = true;
   ThreadCreationImage = std::thread(&VideoAnalyzer::CreerImage, this);

	RunAffichage = true;
	ThreadAffichage = std::thread(&VideoAnalyzer::Afficher, this);
}

void VideoAnalyzer::Stop()
{
	RunAffichage = false;
	ThreadAffichage.join();

   RunCreerImage = false;
   ThreadCreationImage.join();

   RunTrouverRobot = false;
   ThreadTrouverRobot.join();

	RunLecture = false;
	ThreadLecture.join();

   m_ImageLue.Clear();
   m_ImageFinale.Clear();
}

//////////////////////////////////////////////////////////////////
// Threads
//////////////////////////////////////////////////////////////////

void VideoAnalyzer::LireFichier()
{
   cv::Mat mat;
	while (RunLecture)
	{
      cv::imread(m_CamImagePath, CV_LOAD_IMAGE_UNCHANGED).copyTo(mat);

      if (!Utility::MatIsNull(mat))
		{
			m_ImageLue.Set(std::move(mat));
		}
	}
}

//void VideoAnalyzer::LireFichier()
//{
//   // Risque plutôt d'être ça.
//   cv::VideoCapture video = cv::VideoCapture();
//   cv::Mat mat;
//   while (RunLecture)
//   {
//   }
//}

void VideoAnalyzer::TrouverRobot()
{
   double MinVal, MaxVal;
   cv::Point MinLoc, MaxLoc;

   while (RunTrouverRobot)
	{
      try
      {
         cv::Mat& Source = m_ImageUpdate.WaitGet(std::chrono::milliseconds(50));

         if (Utility::MatIsNull(m_IRobotTemplate))
         {
            cv::matchTemplate(Source, m_IRobotTemplate, Source, CV_TM_CCORR);
            cv::minMaxLoc(Source, &MinVal, &MaxVal, &MinLoc, &MaxLoc, 0);

            if (MaxVal >= PRECISION_TEMPLATEMATCHING())
            {
               m_Game->m_Gameplay.m_IRobotPos.x = MaxLoc.x;
               m_Game->m_Gameplay.m_IRobotPos.y = MaxLoc.y;
            }
         }
		}
      catch (NullException)
		{
		}
	}
}

void VideoAnalyzer::CreerImage()
{
   while (RunCreerImage)
   {
      try
      {
         cv::Mat&& temp = m_ImageLue.WaitGet(std::chrono::milliseconds(50));
         m_ImageUpdate.Set(std::move(temp.clone()));

         m_ImageFinale.Set(m_Game->m_Gameplay.ModifierImage(Utility::DrawRectImageOnMat(*m_IRobotRect.get(), std::move(temp))));
      }
      catch (NullException)
      {
      }
   }
}

void VideoAnalyzer::Afficher()
{
	while (RunAffichage)
	{
		try
      {
         cv::Mat&& source = m_ImageFinale.WaitGet(std::chrono::milliseconds(50));

         m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(std::move(source)));
		}
      catch (NullException)
		{
		}
	}
}