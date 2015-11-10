#pragma once

#include <memory>

#include "Gameplay.h"
#include "VideoAnalyzer.h"
#include "qtcyberserpent.h"
#include "ControleIRobot.h"
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
   friend Gameplay;

	const std::chrono::milliseconds REFRESH_RATE =
		std::chrono::milliseconds(0);

	Gameplay m_Gameplay;
	ControleIRobot m_IRobot;
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

};