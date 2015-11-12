#pragma once

#include <memory>
#include <string>
#include <thread>
#include <mutex>

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include "DoubleBuffer.h"
#include "Collision.h"


class CyberSerpent;

class VideoAnalyzer
{
	CyberSerpent* m_Game;
	std::string m_CamNumber;
   cv::Mat m_IRobotTemplate;

public:
   RectCollision m_IRobotRect;
	VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

   void Start(int camNum);

	void Stop();

private:

   bool RunCaptureImage;
   std::thread ThreadCaptureImage;
   void CaptureImage();

   DoubleBuffer_Copie<cv::Mat> m_ImageLue;

   bool RunAnalyse;
   std::thread ThreadAnalyse;
   void Analyse();
};