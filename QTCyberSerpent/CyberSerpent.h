#pragma once

#include <memory>

#include "Gameplay.h"
#include "IRobotDriver.h"
#include "VideoAnalyzer.h"
#include "qtcyberserpent.h"
#include "Utility.h"

enum CyberSerpentState
{
   Uninitialized,
   Initialized,
   Started,
   Stopped
};

class CyberSerpent
{
	friend QTCyberSerpent;
	friend VideoAnalyzer;

	const std::chrono::milliseconds REFRESH_RATE =
		std::chrono::milliseconds(10);

	Gameplay m_Gameplay;
	IRobot::IRobot m_IRobotDriver;
	QApplication m_QTApplication;
	QTCyberSerpent m_QTCyberSerpent;
	VideoAnalyzer m_VideoAnalyzer;

   CyberSerpentState m_State;
   bool m_IsExecuting;
public:

	CyberSerpent(int argc, char *argv[]);
	~CyberSerpent();

	bool Initialize();

	void Start();

   void Afficher();

   void Stop();

   void Delete();

private:

	void OnLeftArrowKeyPress();
   void OnRightArrowKeyPress();
   void OnUpArrowKeyPress();
   void OnDownArrowKeyPress();

};