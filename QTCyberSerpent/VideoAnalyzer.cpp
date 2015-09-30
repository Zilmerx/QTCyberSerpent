#include "VideoAnalyzer.h"
#include "CyberSerpent.h"

VideoAnalyzer::VideoAnalyzer()
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
   ThreadLecture = std::thread(&VideoAnalyzer::LireFichier, this, s);
}

void VideoAnalyzer::LireFichier(std::string path)
{
   cv::Mat mat;
   while (true)
   {
      cv::imread(path, CV_LOAD_IMAGE_UNCHANGED).copyTo(mat);

      if (mat.data)
      {
         m_Image.Set(mat);
         m_Image.Switch();
      }
   }
}