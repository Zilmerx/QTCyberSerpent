#pragma once

#include <memory>

#include "Gameplay.h"
#include "IRobotDriver.h"
#include "VideoAnalyzer.h"
#include "qtcyberserpent.h"

class CyberSerpent
{
	Gameplay m_Gameplay;
	IRobot::IRobot m_IRobotDriver;
   VideoAnalyzer m_VideoAnalyzer;
   QApplication m_QTApplication;
   //QTCyberSerpent m_QTCyberSerpent;

	bool m_Initialized;
public:

   QTCyberSerpent m_QTCyberSerpent;

   CyberSerpent(int argc, char *argv[]);
	~CyberSerpent();

	bool Initialize();

	void Start();

private:

	void TournerRobotGauche();
	void TournerRobotDroite();

};