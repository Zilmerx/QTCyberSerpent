#include "VideoAnalyzer.h"
#include "CyberSerpent.h"
#include "Utility.h"

VideoAnalyzer::VideoAnalyzer() : RunLecture{ false }, RunAffichage{ false }
{
}

VideoAnalyzer::~VideoAnalyzer()
{
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
   RunLecture = true;
   ThreadLecture = std::thread(&VideoAnalyzer::LireFichier, this, s);
   RunAffichage = true;
   ThreadAffichage = std::thread(&VideoAnalyzer::Afficher, this);
}

void VideoAnalyzer::Stop()
{
   RunAffichage = false;
   ThreadAffichage.join();
   RunLecture = false;
   ThreadLecture.join();
}

void VideoAnalyzer::LireFichier(std::string path)
{
   cv::Mat mat;
   while (RunLecture)
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
   while (RunAffichage)
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