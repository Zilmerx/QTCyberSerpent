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

   m_IRobotTemplate = cv::imread("templateIRobot.bmp", CV_LOAD_IMAGE_UNCHANGED);
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

		if (!mat.empty() && mat.data && mat.rows > 0 && mat.cols > 0)
		{
			m_ImageLue.Set(mat);
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
         cv::Mat Source = m_ImageLue.Get().clone();

         cv::matchTemplate(Source, m_IRobotTemplate, Source, CV_TM_CCORR);
         cv::minMaxLoc(Source, &MinVal, &MaxVal, &MinLoc, &MaxLoc,0);

         if (MaxVal >= PRECISION_TEMPLATEMATCHING())
         {
            m_Game->m_Gameplay.m_IRobotPos.x = MaxLoc.x;
            m_Game->m_Gameplay.m_IRobotPos.y = MaxLoc.y;
         }
		}
		catch (...)
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
         m_ImageFinale.Set(m_Game->m_Gameplay.ModifierImage(m_ImageLue.Get()));
      }
      catch (...)
      {
      }
   }
}

void VideoAnalyzer::Afficher()
{
   cv::Mat temp;
	while (RunAffichage)
	{
		try
      {
         m_Game->m_QTCyberSerpent.UI_PutImage(Utility::Mat2QImage(m_ImageFinale.Get()));
		}
		catch (...)
		{
		}
	}
}