#pragma once

#include <memory>
#include <string>

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"


class CyberSerpent;

class VideoAnalyzer
{
	CyberSerpent* m_Game;

public:
	VideoAnalyzer();
	~VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

   cv::Mat LireFichier(std::string path);
};