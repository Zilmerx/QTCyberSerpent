
#include "CyberSerpent.h"
#include <qtimer.h>


CyberSerpent::CyberSerpent(int argc, char *argv[], const std::string camImagePath)
	: m_Gameplay{},
	m_IRobotDriver{},
	m_QTApplication{ argc, argv },
	m_QTCyberSerpent{},
	m_VideoAnalyzer{ camImagePath },
	m_Initialized{ false }
{
   m_QTCyberSerpent.show();

   m_QTCyberSerpent.SetFunc(Qt::Key_Left, std::bind(&CyberSerpent::TournerRobotGauche, this));
   m_QTCyberSerpent.SetFunc(Qt::Key_Right, std::bind(&CyberSerpent::TournerRobotDroite, this));
}

CyberSerpent::~CyberSerpent()
{
   m_VideoAnalyzer.Stop();
   m_Gameplay.Stop();
   m_QTCyberSerpent.Stop();
}


bool CyberSerpent::Initialize()
{
   Utility::Initialize();

	//if (!m_IRobotDriver.Initialize())
	//	return false;

	m_VideoAnalyzer.Initialize(this);
   m_Gameplay.Initialize();
   m_QTCyberSerpent.Initialize(this);

	m_Initialized = true;
	return true;
}

void CyberSerpent::Start()
{
	if (!m_Initialized)
		return;

	m_VideoAnalyzer.Start();
   m_Gameplay.Start();

	m_QTApplication.exec();
}

void CyberSerpent::TournerRobotGauche()
{
   m_QTCyberSerpent.PutError("GAUCHE");
	m_IRobotDriver.Gauche(100, 75);
}

void CyberSerpent::TournerRobotDroite()
{
   m_QTCyberSerpent.PutError("DROITE");
	m_IRobotDriver.Droite(100, 75);
}
