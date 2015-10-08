#pragma once

#include <memory>

#include "Gameplay.h"
#include "IRobotDriver.h"
#include "VideoAnalyzer.h"
#include "qtcyberserpent.h"
#include "Utility.h"

class CyberSerpent
{
	friend QTCyberSerpent;
	friend VideoAnalyzer;

	const std::chrono::milliseconds REFRESH_RATE =
		std::chrono::milliseconds(100);

	Gameplay m_Gameplay;
	IRobot::IRobot m_IRobotDriver;
	QApplication m_QTApplication;
	QTCyberSerpent m_QTCyberSerpent;
	VideoAnalyzer m_VideoAnalyzer;

	bool m_Initialized;
public:

	CyberSerpent(int argc, char *argv[], const std::string imagepath);
	~CyberSerpent();

	bool Initialize();

	void Start();

private:

	void TournerRobotGauche();
	void TournerRobotDroite();

};