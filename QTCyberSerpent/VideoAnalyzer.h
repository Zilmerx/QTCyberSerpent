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
	const std::string m_CamImagePath;

public:

	VideoAnalyzer(const std::string camImagePath);
	~VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

	void Start();

	void Stop();

private:
	// Thread qui prend le fichier dans le path, le convertis en Mat, 
	// puis le met dans m_ImageLue;
	bool RunLecture;
	std::thread ThreadLecture;
	void LireFichier();

	DoubleBuffer<cv::Mat> m_ImageLue;

	// Thread qui prend le Mat dans m_ImageLue, l'analyse et la modifie,
	// puis le met dans m_ImageAnalysee;
	bool RunAnalyse;
	std::thread ThreadAnalyse;
	void Analyser();

	DoubleBuffer<cv::Mat> m_ImageAnalysee;

	// Thread qui prend le Mat dans m_ImageAnalysee, la convertis en 
	// QPixmap puis demande à l'interface de l'afficher.
	bool RunAffichage;
	std::thread ThreadAffichage;
	void Afficher();

};