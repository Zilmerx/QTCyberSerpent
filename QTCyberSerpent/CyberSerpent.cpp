
#include "CyberSerpent.h"
#include <qtimer.h>

void DoShit()
{
   QMessageBox b;
   b.setText("HERPDERP");
   b.show();
}

CyberSerpent::CyberSerpent(int argc, char *argv[], const std::string camImagePath)
	: m_Gameplay{},
	m_IRobotDriver{},
	m_QTApplication{ argc, argv },
	m_QTCyberSerpent{},
	m_VideoAnalyzer{ camImagePath },
	m_Initialized{ false }
{
   m_QTCyberSerpent.show();

   m_QTCyberSerpent.SetFunc(Qt::Key_Enter, std::bind(DoShit));
}

CyberSerpent::~CyberSerpent()
{
   m_VideoAnalyzer.Stop();
   m_QTCyberSerpent.Stop();
}


bool CyberSerpent::Initialize()
{
	//if (!m_IRobotDriver.Initialize())
	//	return false;

	m_VideoAnalyzer.Initialize(this);
   m_QTCyberSerpent.Initialize(this);

	m_Initialized = true;
	return true;
}

void CyberSerpent::Start()
{
	if (!m_Initialized)
		return;

	m_VideoAnalyzer.Start();

	m_QTApplication.exec();
}

void CyberSerpent::TournerRobotGauche()
{
	std::cout << "GAUCHE" << std::endl;
	m_IRobotDriver.Gauche(100, 75);
}

void CyberSerpent::TournerRobotDroite()
{
	std::cout << "DROITE" << std::endl;
	m_IRobotDriver.Droite(100, 75);
}
