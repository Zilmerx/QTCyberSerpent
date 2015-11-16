#pragma once

#include <memory>
#include <thread>
#include <mutex>

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include "Gameplay.h"
#include "DoubleBuffer.h"
#include "Collision.h"


class CyberSerpent;

class VideoAnalyzer
{
   friend class CyberSerpent;

   Gameplay m_Gameplay;
	CyberSerpent* m_Game;

   cv::VideoCapture cap;

public:
	VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

   void Start(int camNum);

	void Stop();

private:

   ThreadWrapper m_CaptureImage;
   void CaptureImage();

   ThreadWrapper m_Affichage;
   void Affichage();
};