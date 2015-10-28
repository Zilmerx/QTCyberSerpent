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
   std::unique_ptr<RectImage> m_IRobotRect;

public:

	VideoAnalyzer();
	~VideoAnalyzer();

	void Initialize(CyberSerpent* linked);

   void Start(std::string path);

	void Stop();

private:
	// Thread qui prend le fichier dans le path, le convertis en Mat, 
	// puis le met dans m_ImageLue;
	bool RunLecture;
	std::thread ThreadLecture;
	void LireFichier();

	DoubleBuffer_Copie<cv::Mat> m_ImageLue;

	// Thread qui prend le Mat dans m_ImageLue, trouve la position du IRobot
   // puis la met dans m_Game->m_Gameplay.m_IRobotPos
   bool RunTrouverRobot;
   std::thread ThreadTrouverRobot;
   void TrouverRobot();

   DoubleBuffer_Copie<cv::Mat> m_ImageUpdate;

   // Créée une nouvelle image en se servant des informations stockées dans
   // la classe de Gameplay.
   bool RunCreerImage;
   std::thread ThreadCreationImage;
   void CreerImage();

   DoubleBuffer_Copie<cv::Mat> m_ImageFinale;

	// Thread qui prend le Mat dans m_ImageAnalysee, la convertis en 
	// QPixmap puis demande à l'interface de l'afficher.
	bool RunAffichage;
	std::thread ThreadAffichage;
	void Afficher();

};