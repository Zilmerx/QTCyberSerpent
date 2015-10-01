#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"

VideoAnalyzer::VideoAnalyzer() : RunThreads{ false }
{
}

VideoAnalyzer::~VideoAnalyzer()
{
   RunThreads = false;
   ThreadLecture.join();
   ThreadAffichage.join();
}

cv::Mat& VideoAnalyzer::GetImage()
{
   try
   {
      return m_Image.Get();
   }
   catch (...)
   {
      throw;
   }
}

void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;
   std::string s = "image.bmp";
   RunThreads = true;

   ThreadLecture = std::thread(&VideoAnalyzer::LireFichier, this, s);
   ThreadAffichage = std::thread(&VideoAnalyzer::Afficher, this);
}

void VideoAnalyzer::LireFichier(std::string path)
{
   cv::Mat mat;
   while (RunThreads)
   {
      cv::imread(path, CV_LOAD_IMAGE_UNCHANGED).copyTo(mat);

      if (mat.data)
      {
         m_Image.Set(mat);
         m_Image.Switch();
      }
   }
}

void VideoAnalyzer::Afficher()
{
   cv::Mat img;
   while (RunThreads)
   {
      try
      {
         m_Game->m_QTCyberSerpent.PutImage(Utility::Mat2QPixmap(m_Image.Get()));
      }
      catch (...)
      {
      }
   }
}