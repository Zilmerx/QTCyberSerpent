#pragma once

#include <memory>
#include <string>
#include <thread>

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include "DoubleBuffer.h"


class CyberSerpent;

class VideoAnalyzer
{
	CyberSerpent* m_Game;

   DoubleBuffer<cv::Mat> m_Image;

   bool RunThreads;

public:

   cv::Mat& GetImage();

	VideoAnalyzer();
	~VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

private:
   // Est utilisée par le thread "ThreadLecture"
   // Fonction qui prend le fichier dans le path, le convertis en Mat, puis le met dans m_Image;
   std::thread ThreadLecture;
   void LireFichier(std::string path);

   std::thread ThreadAffichage;
   void Afficher();

};