#include "VideoAnalyzer.h"

VideoAnalyzer::VideoAnalyzer()
{
}

VideoAnalyzer::~VideoAnalyzer()
{

}

void VideoAnalyzer::Initialize(CyberSerpent* linked)
{
	m_Game = linked;
}

cv::Mat LireFichier(std::string path)
{
   return cv::imread(path, CV_LOAD_IMAGE_COLOR);   // Read the file
}