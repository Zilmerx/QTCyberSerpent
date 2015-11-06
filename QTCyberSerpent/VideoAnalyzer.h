#pragma once

#include <memory>
#include <string>
#include <thread>
#include <mutex>

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include "DoubleBuffer.h"
#include "RectImage.h"


class CyberSerpent;

class VideoAnalyzer
{
   static double PRECISION_TEMPLATEMATCHING()
   {
      return 0.8;
   }

	CyberSerpent* m_Game;
	std::string m_CamImagePath;
   cv::Mat m_IRobotTemplate;
   //std::unique_ptr<RectImage> m_IRobotRect;

public:
   RectImage m_IRobotRect;
	VideoAnalyzer();
	~VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

   void Start(std::string path);

	void Stop();

private:

   bool RunDo;
   std::thread ThreadDo;
   void Do();
};