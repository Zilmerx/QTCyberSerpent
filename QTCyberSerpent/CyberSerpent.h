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

	ControleIRobot m_IRobot;
	QApplication m_QTApplication;
	QTCyberSerpent m_QTCyberSerpent;
	VideoAnalyzer m_VideoAnalyzer;

   CyberSerpentState m_State;
   bool m_IsExecuting;
public:

   static std::unique_ptr<CyberSerpent> Creer_CyberSerpent(int argc, char *argv[]);

   void Afficher();

   ~CyberSerpent();

private:

   CyberSerpent(int argc, char *argv[]);

   bool Initialize();

	void Start();

   void Stop();

   void Delete();
};