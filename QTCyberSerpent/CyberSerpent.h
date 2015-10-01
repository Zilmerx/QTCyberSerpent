#pragma once

#include <memory>

#include "Gameplay.h"
#include "IRobotDriver.h"
#include "VideoAnalyzer.h"
#include "qtcyberserpent.h"

class CyberSerpent
{
   friend QTCyberSerpent;
   friend VideoAnalyzer;

   const std::chrono::milliseconds REFRESH_RATE =
      std::chrono::milliseconds(200);

	Gameplay m_Gameplay;
	IRobot::IRobot m_IRobotDriver;
   QApplication m_QTApplication;
   VideoAnalyzer m_VideoAnalyzer;
   QTCyberSerpent m_QTCyberSerpent;

	bool m_Initialized;
public:

   CyberSerpent(int argc, char *argv[]);
	~CyberSerpent();

	bool Initialize();

	void Start();

private:

	void TournerRobotGauche();
	void TournerRobotDroite();

};