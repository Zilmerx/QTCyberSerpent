#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"

VideoAnalyzer::VideoAnalyzer(const std::string camImagePath) 
	: m_CamImagePath{ camImagePath }, 
	RunLecture{ false }, 
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

   cv::imread("templateIRobot.bmp", CV_LOAD_IMAGE_UNCHANGED).copyTo(m_IRobotTemplate);
}

void VideoAnalyzer::Start()
{
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

		if (mat.data)
		{
			m_ImageLue.Set(mat);
			//m_ImageLue.Switch();
		}
	}
}

//void VideoAnalyzer::LireFichier()
//{
//   // Risque plutôt d'être ça.
//
//   cv::VideoCapture video = cv::VideoCapture();
//}

void VideoAnalyzer::TrouverRobot()
{
   cv::Mat Source;

   double MinVal, MaxVal;
   cv::Point MinLoc, MaxLoc;

   while (RunTrouverRobot)
	{
		try
		{
         m_ImageLue.Get().copyTo(Source); // Copie voulue : Il ne faut pas modifier l'image lue, et le templatematching modifie l'image.

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
   cv::Mat* mat;

   while (RunCreerImage)
   {
      try
      {
         mat = &m_ImageLue.Get();

         // Modification de l'image.

         m_ImageFinale.Set(*mat);
         //m_ImageAnalysee.Switch();
      }
      catch (...)
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
         m_Game->m_QTCyberSerpent.PutImage(Utility::Mat2QPixmap(m_ImageFinale.Get()));
		}
		catch (...)
		{
		}
	}
}